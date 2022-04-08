#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>


#include "esp_err.h"
#include "driver/ledc.h"
#include "sensor.h"
#include "sys/time.h"

#include "img_converters.h"

#include "time.h"
#include "sys/time.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
//#include "sensor.h"
#include "sccb.h"
#include "cam_hal.h"
//#include "esp_camera.h"
#include "xclk.h"

/**********************************    SENSOR        **********************/
  
#ifndef __SENSOR_H__
#define __SENSOR_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    OV9650_PID = 0x96,
    OV7725_PID = 0x77,
    OV2640_PID = 0x26,
    OV3660_PID = 0x3660,
    OV5640_PID = 0x5640,
    OV7670_PID = 0x76,
    NT99141_PID = 0x1410,
    GC2145_PID = 0x2145,
    GC032A_PID = 0x232a,
    GC0308_PID = 0x9b,
    BF3005_PID = 0x30,
    BF20A6_PID = 0x20a6,
} camera_pid_t;

typedef enum {
    CAMERA_OV7725,
    CAMERA_OV2640,
    CAMERA_OV3660,
    CAMERA_OV5640,
    CAMERA_OV7670,
    CAMERA_NT99141,
    CAMERA_GC2145,
    CAMERA_GC032A,
    CAMERA_GC0308,
    CAMERA_BF3005,
    CAMERA_BF20A6,
    CAMERA_MODEL_MAX,
    CAMERA_NONE,
} camera_model_t;

typedef enum {
    OV2640_SCCB_ADDR   = 0x30,// 0x60 >> 1
    OV5640_SCCB_ADDR   = 0x3C,// 0x78 >> 1
    OV3660_SCCB_ADDR   = 0x3C,// 0x78 >> 1
    OV7725_SCCB_ADDR   = 0x21,// 0x42 >> 1
    OV7670_SCCB_ADDR   = 0x21,// 0x42 >> 1
    NT99141_SCCB_ADDR  = 0x2A,// 0x54 >> 1
    GC2145_SCCB_ADDR   = 0x3C,// 0x78 >> 1
    GC032A_SCCB_ADDR   = 0x21,// 0x42 >> 1
    GC0308_SCCB_ADDR   = 0x21,// 0x42 >> 1
    BF3005_SCCB_ADDR   = 0x6E,
    BF20A6_SCCB_ADDR   = 0x6E,
} camera_sccb_addr_t;

typedef enum {
    PIXFORMAT_RGB565,    // 2BPP/RGB565
    PIXFORMAT_YUV422,    // 2BPP/YUV422
    PIXFORMAT_GRAYSCALE, // 1BPP/GRAYSCALE
    PIXFORMAT_JPEG,      // JPEG/COMPRESSED
    PIXFORMAT_RGB888,    // 3BPP/RGB888
    PIXFORMAT_RAW,       // RAW
    PIXFORMAT_RGB444,    // 3BP2P/RGB444
    PIXFORMAT_RGB555,    // 3BP2P/RGB555
} pixformat_t;

typedef enum {
    FRAMESIZE_96X96,    // 96x96
    FRAMESIZE_QQVGA,    // 160x120
    FRAMESIZE_QCIF,     // 176x144
    FRAMESIZE_HQVGA,    // 240x176
    FRAMESIZE_240X240,  // 240x240
    FRAMESIZE_QVGA,     // 320x240
    FRAMESIZE_CIF,      // 400x296
    FRAMESIZE_HVGA,     // 480x320
    FRAMESIZE_VGA,      // 640x480
    FRAMESIZE_SVGA,     // 800x600
    FRAMESIZE_XGA,      // 1024x768
    FRAMESIZE_HD,       // 1280x720
    FRAMESIZE_SXGA,     // 1280x1024
    FRAMESIZE_UXGA,     // 1600x1200
    // 3MP Sensors
    FRAMESIZE_FHD,      // 1920x1080
    FRAMESIZE_P_HD,     //  720x1280
    FRAMESIZE_P_3MP,    //  864x1536
    FRAMESIZE_QXGA,     // 2048x1536
    // 5MP Sensors
    FRAMESIZE_QHD,      // 2560x1440
    FRAMESIZE_WQXGA,    // 2560x1600
    FRAMESIZE_P_FHD,    // 1080x1920
    FRAMESIZE_QSXGA,    // 2560x1920
    FRAMESIZE_INVALID
} framesize_t;

typedef struct {
    const camera_model_t model;
    const char *name;
    const camera_sccb_addr_t sccb_addr;
    const camera_pid_t pid;
    const framesize_t max_size;
    const bool support_jpeg;
} camera_sensor_info_t;

typedef enum {
    ASPECT_RATIO_4X3,
    ASPECT_RATIO_3X2,
    ASPECT_RATIO_16X10,
    ASPECT_RATIO_5X3,
    ASPECT_RATIO_16X9,
    ASPECT_RATIO_21X9,
    ASPECT_RATIO_5X4,
    ASPECT_RATIO_1X1,
    ASPECT_RATIO_9X16
} aspect_ratio_t;

typedef enum {
    GAINCEILING_2X,
    GAINCEILING_4X,
    GAINCEILING_8X,
    GAINCEILING_16X,
    GAINCEILING_32X,
    GAINCEILING_64X,
    GAINCEILING_128X,
} gainceiling_t;

typedef struct {
        uint16_t max_width;
        uint16_t max_height;
        uint16_t start_x;
        uint16_t start_y;
        uint16_t end_x;
        uint16_t end_y;
        uint16_t offset_x;
        uint16_t offset_y;
        uint16_t total_x;
        uint16_t total_y;
} ratio_settings_t;

typedef struct {
        const uint16_t width;
        const uint16_t height;
        const aspect_ratio_t aspect_ratio;
} resolution_info_t;

// Resolution table (in sensor.c)
extern const resolution_info_t resolution[];
// camera sensor table (in sensor.c)
extern const camera_sensor_info_t camera_sensor[];

typedef struct {
    uint8_t MIDH;
    uint8_t MIDL;
    uint16_t PID;
    uint8_t VER;
} sensor_id_t;

typedef struct {
    framesize_t framesize;//0 - 10
    bool scale;
    bool binning;
    uint8_t quality;//0 - 63
    int8_t brightness;//-2 - 2
    int8_t contrast;//-2 - 2
    int8_t saturation;//-2 - 2
    int8_t sharpness;//-2 - 2
    uint8_t denoise;
    uint8_t special_effect;//0 - 6
    uint8_t wb_mode;//0 - 4
    uint8_t awb;
    uint8_t awb_gain;
    uint8_t aec;
    uint8_t aec2;
    int8_t ae_level;//-2 - 2
    uint16_t aec_value;//0 - 1200
    uint8_t agc;
    uint8_t agc_gain;//0 - 30
    uint8_t gainceiling;//0 - 6
    uint8_t bpc;
    uint8_t wpc;
    uint8_t raw_gma;
    uint8_t lenc;
    uint8_t hmirror;
    uint8_t vflip;
    uint8_t dcw;
    uint8_t colorbar;
} camera_status_t;

typedef struct _sensor sensor_t;
typedef struct _sensor {
    sensor_id_t id;             // Sensor ID.
    uint8_t  slv_addr;          // Sensor I2C slave address.
    pixformat_t pixformat;
    camera_status_t status;
    int xclk_freq_hz;

    // Sensor function pointers
    int  (*init_status)         (sensor_t *sensor);
    int  (*reset)               (sensor_t *sensor);
    int  (*set_pixformat)       (sensor_t *sensor, pixformat_t pixformat);
    int  (*set_framesize)       (sensor_t *sensor, framesize_t framesize);
    int  (*set_contrast)        (sensor_t *sensor, int level);
    int  (*set_brightness)      (sensor_t *sensor, int level);
    int  (*set_saturation)      (sensor_t *sensor, int level);
    int  (*set_sharpness)       (sensor_t *sensor, int level);
    int  (*set_denoise)         (sensor_t *sensor, int level);
    int  (*set_gainceiling)     (sensor_t *sensor, gainceiling_t gainceiling);
    int  (*set_quality)         (sensor_t *sensor, int quality);
    int  (*set_colorbar)        (sensor_t *sensor, int enable);
    int  (*set_whitebal)        (sensor_t *sensor, int enable);
    int  (*set_gain_ctrl)       (sensor_t *sensor, int enable);
    int  (*set_exposure_ctrl)   (sensor_t *sensor, int enable);
    int  (*set_hmirror)         (sensor_t *sensor, int enable);
    int  (*set_vflip)           (sensor_t *sensor, int enable);

    int  (*set_aec2)            (sensor_t *sensor, int enable);
    int  (*set_awb_gain)        (sensor_t *sensor, int enable);
    int  (*set_agc_gain)        (sensor_t *sensor, int gain);
    int  (*set_aec_value)       (sensor_t *sensor, int gain);

    int  (*set_special_effect)  (sensor_t *sensor, int effect);
    int  (*set_wb_mode)         (sensor_t *sensor, int mode);
    int  (*set_ae_level)        (sensor_t *sensor, int level);

    int  (*set_dcw)             (sensor_t *sensor, int enable);
    int  (*set_bpc)             (sensor_t *sensor, int enable);
    int  (*set_wpc)             (sensor_t *sensor, int enable);

    int  (*set_raw_gma)         (sensor_t *sensor, int enable);
    int  (*set_lenc)            (sensor_t *sensor, int enable);

    int  (*get_reg)             (sensor_t *sensor, int reg, int mask);
    int  (*set_reg)             (sensor_t *sensor, int reg, int mask, int value);
    int  (*set_res_raw)         (sensor_t *sensor, int startX, int startY, int endX, int endY, int offsetX, int offsetY, int totalX, int totalY, int outputX, int outputY, bool scale, bool binning);
    int  (*set_pll)             (sensor_t *sensor, int bypass, int mul, int sys, int root, int pre, int seld5, int pclken, int pclk);
    int  (*set_xclk)            (sensor_t *sensor, int timer, int xclk);
} sensor_t;

camera_sensor_info_t *esp_camera_sensor_get_info(sensor_id_t *id);

#ifdef __cplusplus
}
#endif

#endif /* __SENSOR_H__ */

#include <stdio.h>
//#include "sensor.h"

const camera_sensor_info_t camera_sensor[CAMERA_MODEL_MAX] = {
    // The sequence must be consistent with camera_model_t
    {CAMERA_OV7725, "OV7725", OV7725_SCCB_ADDR, OV7725_PID, FRAMESIZE_VGA, false},
    {CAMERA_OV2640, "OV2640", OV2640_SCCB_ADDR, OV2640_PID, FRAMESIZE_UXGA, true},
    {CAMERA_OV3660, "OV3660", OV3660_SCCB_ADDR, OV3660_PID, FRAMESIZE_QXGA, true},
    {CAMERA_OV5640, "OV5640", OV5640_SCCB_ADDR, OV5640_PID, FRAMESIZE_QSXGA, true},
    {CAMERA_OV7670, "OV7670", OV7670_SCCB_ADDR, OV7670_PID, FRAMESIZE_VGA, false},
    {CAMERA_NT99141, "NT99141", NT99141_SCCB_ADDR, NT99141_PID, FRAMESIZE_HD, true},
    {CAMERA_GC2145, "GC2145", GC2145_SCCB_ADDR, GC2145_PID, FRAMESIZE_UXGA, false},
    {CAMERA_GC032A, "GC032A", GC032A_SCCB_ADDR, GC032A_PID, FRAMESIZE_VGA, false},
    {CAMERA_GC0308, "GC0308", GC0308_SCCB_ADDR, GC0308_PID, FRAMESIZE_VGA, false},
    {CAMERA_BF3005, "BF3005", BF3005_SCCB_ADDR, BF3005_PID, FRAMESIZE_VGA, false},
    {CAMERA_BF20A6, "BF20A6", BF20A6_SCCB_ADDR, BF20A6_PID, FRAMESIZE_VGA, false},
};

const resolution_info_t resolution[FRAMESIZE_INVALID] = {
    {   96,   96, ASPECT_RATIO_1X1   }, /* 96x96 */
    {  160,  120, ASPECT_RATIO_4X3   }, /* QQVGA */
    {  176,  144, ASPECT_RATIO_5X4   }, /* QCIF  */
    {  240,  176, ASPECT_RATIO_4X3   }, /* HQVGA */
    {  240,  240, ASPECT_RATIO_1X1   }, /* 240x240 */
    {  320,  240, ASPECT_RATIO_4X3   }, /* QVGA  */
    {  400,  296, ASPECT_RATIO_4X3   }, /* CIF   */
    {  480,  320, ASPECT_RATIO_3X2   }, /* HVGA  */
    {  640,  480, ASPECT_RATIO_4X3   }, /* VGA   */
    {  800,  600, ASPECT_RATIO_4X3   }, /* SVGA  */
    { 1024,  768, ASPECT_RATIO_4X3   }, /* XGA   */
    { 1280,  720, ASPECT_RATIO_16X9  }, /* HD    */
    { 1280, 1024, ASPECT_RATIO_5X4   }, /* SXGA  */
    { 1600, 1200, ASPECT_RATIO_4X3   }, /* UXGA  */
    // 3MP Sensors
    { 1920, 1080, ASPECT_RATIO_16X9  }, /* FHD   */
    {  720, 1280, ASPECT_RATIO_9X16  }, /* Portrait HD   */
    {  864, 1536, ASPECT_RATIO_9X16  }, /* Portrait 3MP   */
    { 2048, 1536, ASPECT_RATIO_4X3   }, /* QXGA  */
    // 5MP Sensors
    { 2560, 1440, ASPECT_RATIO_16X9  }, /* QHD    */
    { 2560, 1600, ASPECT_RATIO_16X10 }, /* WQXGA  */
    { 1088, 1920, ASPECT_RATIO_9X16  }, /* Portrait FHD   */
    { 2560, 1920, ASPECT_RATIO_4X3   }, /* QSXGA  */
};

camera_sensor_info_t *esp_camera_sensor_get_info(sensor_id_t *id)
{
    for (int i = 0; i < CAMERA_MODEL_MAX; i++) {
        if (id->PID == camera_sensor[i].pid) {
            return (camera_sensor_info_t *)&camera_sensor[i];
        }
    }
    return NULL;
}



/**********************************    ESPCAMERA        **********************/
  

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CAMERA_GRAB_WHEN_EMPTY,         /*!< Fills buffers when they are empty. Less resources but first 'fb_count' frames might be old */
    CAMERA_GRAB_LATEST              /*!< Except when 1 frame buffer is used, queue will always contain the last 'fb_count' frames */
} camera_grab_mode_t;

typedef enum {
    CAMERA_FB_IN_PSRAM,         /*!< Frame buffer is placed in external PSRAM */
    CAMERA_FB_IN_DRAM           /*!< Frame buffer is placed in internal DRAM */
} camera_fb_location_t;

typedef struct {
    int pin_pwdn;                   /*!< GPIO pin for camera power down line */
    int pin_reset;                  /*!< GPIO pin for camera reset line */
    int pin_xclk;                   /*!< GPIO pin for camera XCLK line */
    int pin_sscb_sda;               /*!< GPIO pin for camera SDA line */
    int pin_sscb_scl;               /*!< GPIO pin for camera SCL line */
    int pin_d7;                     /*!< GPIO pin for camera D7 line */
    int pin_d6;                     /*!< GPIO pin for camera D6 line */
    int pin_d5;                     /*!< GPIO pin for camera D5 line */
    int pin_d4;                     /*!< GPIO pin for camera D4 line */
    int pin_d3;                     /*!< GPIO pin for camera D3 line */
    int pin_d2;                     /*!< GPIO pin for camera D2 line */
    int pin_d1;                     /*!< GPIO pin for camera D1 line */
    int pin_d0;                     /*!< GPIO pin for camera D0 line */
    int pin_vsync;                  /*!< GPIO pin for camera VSYNC line */
    int pin_href;                   /*!< GPIO pin for camera HREF line */
    int pin_pclk;                   /*!< GPIO pin for camera PCLK line */

    int xclk_freq_hz;               /*!< Frequency of XCLK signal, in Hz. EXPERIMENTAL: Set to 16MHz on ESP32-S2 or ESP32-S3 to enable EDMA mode */

    ledc_timer_t ledc_timer;        /*!< LEDC timer to be used for generating XCLK  */
    ledc_channel_t ledc_channel;    /*!< LEDC channel to be used for generating XCLK  */

    pixformat_t pixel_format;       /*!< Format of the pixel data: PIXFORMAT_ + YUV422|GRAYSCALE|RGB565|JPEG  */
    framesize_t frame_size;         /*!< Size of the output image: FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA  */

    int jpeg_quality;               /*!< Quality of JPEG output. 0-63 lower means higher quality  */
    size_t fb_count;                /*!< Number of frame buffers to be allocated. If more than one, then each frame will be acquired (double speed)  */
    camera_fb_location_t fb_location; /*!< The location where the frame buffer will be allocated */
    camera_grab_mode_t grab_mode;   /*!< When buffers should be filled */
} camera_config_t;

typedef struct {
    uint8_t * buf;              /*!< Pointer to the pixel data */
    size_t len;                 /*!< Length of the buffer in bytes */
    size_t width;               /*!< Width of the buffer in pixels */
    size_t height;              /*!< Height of the buffer in pixels */
    pixformat_t format;         /*!< Format of the pixel data */
    struct timeval timestamp;   /*!< Timestamp since boot of the first DMA buffer of the frame */
} camera_fb_t;

#define ESP_ERR_CAMERA_BASE 0x20000
#define ESP_ERR_CAMERA_NOT_DETECTED             (ESP_ERR_CAMERA_BASE + 1)
#define ESP_ERR_CAMERA_FAILED_TO_SET_FRAME_SIZE (ESP_ERR_CAMERA_BASE + 2)
#define ESP_ERR_CAMERA_FAILED_TO_SET_OUT_FORMAT (ESP_ERR_CAMERA_BASE + 3)
#define ESP_ERR_CAMERA_NOT_SUPPORTED            (ESP_ERR_CAMERA_BASE + 4)


#if CONFIG_OV2640_SUPPORT
#include "ov2640.h"
#endif
#if CONFIG_OV7725_SUPPORT
#include "ov7725.h"
#endif
#if CONFIG_OV3660_SUPPORT
#include "ov3660.h"
#endif
#if CONFIG_OV5640_SUPPORT
#include "ov5640.h"
#endif
#if CONFIG_NT99141_SUPPORT
#include "nt99141.h"
#endif
#if CONFIG_OV7670_SUPPORT
#include "ov7670.h"
#endif
#if CONFIG_GC2145_SUPPORT
#include "gc2145.h"
#endif
#if CONFIG_GC032A_SUPPORT
#include "gc032a.h"
#endif
#if CONFIG_GC0308_SUPPORT
#include "gc0308.h"
#endif
#if CONFIG_BF3005_SUPPORT
#include "bf3005.h"
#endif
#if CONFIG_BF20A6_SUPPORT
#include "bf20a6.h"
#endif

#if defined(ARDUINO_ARCH_ESP32) && defined(CONFIG_ARDUHAL_ESP_LOG)
#include "esp32-hal-log.h"
#define TAG ""
#else
#include "esp_log.h"
static const char *TAG = "camera";
#endif

typedef struct {
    sensor_t sensor;
    camera_fb_t fb;
} camera_state_t;

typedef struct {
    int (*detect)(int slv_addr, sensor_id_t *id);
    int (*init)(sensor_t *sensor);
} sensor_func_t;

static const char *CAMERA_SENSOR_NVS_KEY = "sensor";
static const char *CAMERA_PIXFORMAT_NVS_KEY = "pixformat";
static camera_state_t *s_state = NULL;

#if CONFIG_IDF_TARGET_ESP32S3 // LCD_CAM module of ESP32-S3 will generate xclk
#define CAMERA_ENABLE_OUT_CLOCK(v)
#define CAMERA_DISABLE_OUT_CLOCK()
#else
#define CAMERA_ENABLE_OUT_CLOCK(v) camera_enable_out_clock((v))
#define CAMERA_DISABLE_OUT_CLOCK() camera_disable_out_clock()
#endif

#ifdef __cplusplus
}
#endif

#define FB_GET_TIMEOUT (4000 / portTICK_PERIOD_MS)

static const sensor_func_t g_sensors[] = {
#if CONFIG_OV7725_SUPPORT
    {ov7725_detect, ov7725_init},
#endif
#if CONFIG_OV7670_SUPPORT
    {ov7670_detect, ov7670_init},
#endif
#if CONFIG_OV2640_SUPPORT
    {ov2640_detect, ov2640_init},
#endif
#if CONFIG_OV3660_SUPPORT
    {ov3660_detect, ov3660_init},
#endif
#if CONFIG_OV5640_SUPPORT
    {ov5640_detect, ov5640_init},
#endif
#if CONFIG_NT99141_SUPPORT
    {nt99141_detect, nt99141_init},
#endif
#if CONFIG_GC2145_SUPPORT
    {gc2145_detect, gc2145_init},
#endif
#if CONFIG_GC032A_SUPPORT
    {gc032a_detect, gc032a_init},
#endif
#if CONFIG_GC0308_SUPPORT
    {gc0308_detect, gc0308_init},
#endif
#if CONFIG_BF3005_SUPPORT
    {bf3005_detect, bf3005_init},
#endif
#if CONFIG_BF20A6_SUPPORT
    {bf20a6_detect, bf20a6_init},
#endif
};

static esp_err_t camera_probe(const camera_config_t *config, camera_model_t *out_camera_model)
{
    *out_camera_model = CAMERA_NONE;
    if (s_state != NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    s_state = (camera_state_t *) calloc(sizeof(camera_state_t), 1);
    if (!s_state) {
        return ESP_ERR_NO_MEM;
    }

    if (config->pin_xclk >= 0) {
        ESP_LOGD(TAG, "Enabling XCLK output");
        CAMERA_ENABLE_OUT_CLOCK(config);
    }

    if (config->pin_sscb_sda != -1) {
        ESP_LOGD(TAG, "Initializing SSCB");
        SCCB_Init(config->pin_sscb_sda, config->pin_sscb_scl);
    }

    if (config->pin_pwdn >= 0) {
        ESP_LOGD(TAG, "Resetting camera by power down line");
        gpio_config_t conf = { 0 };
        conf.pin_bit_mask = 1LL << config->pin_pwdn;
        conf.mode = GPIO_MODE_OUTPUT;
        gpio_config(&conf);

        // carefull, logic is inverted compared to reset pin
        gpio_set_level(config->pin_pwdn, 1);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        gpio_set_level(config->pin_pwdn, 0);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    if (config->pin_reset >= 0) {
        ESP_LOGD(TAG, "Resetting camera");
        gpio_config_t conf = { 0 };
        conf.pin_bit_mask = 1LL << config->pin_reset;
        conf.mode = GPIO_MODE_OUTPUT;
        gpio_config(&conf);

        gpio_set_level(config->pin_reset, 0);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        gpio_set_level(config->pin_reset, 1);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }


    ESP_LOGD(TAG, "Searching for camera address");
    vTaskDelay(10 / portTICK_PERIOD_MS);

    uint8_t slv_addr = SCCB_Probe();

    if (slv_addr == 0) {
        CAMERA_DISABLE_OUT_CLOCK();
        return ESP_ERR_NOT_FOUND;
    }

    ESP_LOGI(TAG, "Detected camera at address=0x%02x", slv_addr);
    s_state->sensor.slv_addr = slv_addr;
    s_state->sensor.xclk_freq_hz = config->xclk_freq_hz;

    /**
     * Read sensor ID and then initialize sensor
     * Attention: Some sensors have the same SCCB address. Therefore, several attempts may be made in the detection process
     */
    sensor_id_t *id = &s_state->sensor.id;
    for (size_t i = 0; i < sizeof(g_sensors) / sizeof(sensor_func_t); i++) {
        if (g_sensors[i].detect(slv_addr, id)) {
            camera_sensor_info_t *info = esp_camera_sensor_get_info(id);
            if (NULL != info) {
                *out_camera_model = info->model;
                ESP_LOGI(TAG, "Detected %s camera", info->name);
                g_sensors[i].init(&s_state->sensor);
                break;
            }
        }
    }

    if (CAMERA_NONE == *out_camera_model) { //If no supported sensors are detected
        CAMERA_DISABLE_OUT_CLOCK();
        ESP_LOGE(TAG, "Detected camera not supported.");
        return ESP_ERR_NOT_SUPPORTED;
    }

    ESP_LOGI(TAG, "Camera PID=0x%02x VER=0x%02x MIDL=0x%02x MIDH=0x%02x",
             id->PID, id->VER, id->MIDH, id->MIDL);

    ESP_LOGD(TAG, "Doing SW reset of sensor");
    vTaskDelay(10 / portTICK_PERIOD_MS);
    s_state->sensor.reset(&s_state->sensor);

    return ESP_OK;
}

esp_err_t esp_camera_init(const camera_config_t *config)//esp_err_t esp_camera_init(const camera_config_t* config);
{
    esp_err_t err;
    err = cam_init(config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Camera init failed with error 0x%x", err);
        return err;
    }

    camera_model_t camera_model = CAMERA_NONE;
    err = camera_probe(config, &camera_model);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Camera probe failed with error 0x%x(%s)", err, esp_err_to_name(err));
        goto fail;
    }

    framesize_t frame_size = (framesize_t) config->frame_size;
    pixformat_t pix_format = (pixformat_t) config->pixel_format;

    if (PIXFORMAT_JPEG == pix_format && (!camera_sensor[camera_model].support_jpeg)) {
        ESP_LOGE(TAG, "JPEG format is not supported on this sensor");
        err = ESP_ERR_NOT_SUPPORTED;
        goto fail;
    }

    if (frame_size > camera_sensor[camera_model].max_size) {
        ESP_LOGW(TAG, "The frame size exceeds the maximum for this sensor, it will be forced to the maximum possible value");
        frame_size = camera_sensor[camera_model].max_size;
    }

    err = cam_config(config, frame_size, s_state->sensor.id.PID);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Camera config failed with error 0x%x", err);
        goto fail;
    }

    s_state->sensor.status.framesize = frame_size;
    s_state->sensor.pixformat = pix_format;
    ESP_LOGD(TAG, "Setting frame size to %dx%d", resolution[frame_size].width, resolution[frame_size].height);
    if (s_state->sensor.set_framesize(&s_state->sensor, frame_size) != 0) {
        ESP_LOGE(TAG, "Failed to set frame size");
        err = ESP_ERR_CAMERA_FAILED_TO_SET_FRAME_SIZE;
        goto fail;
    }
    s_state->sensor.set_pixformat(&s_state->sensor, pix_format);

    if (s_state->sensor.id.PID == OV2640_PID) {
        s_state->sensor.set_gainceiling(&s_state->sensor, GAINCEILING_2X);
        s_state->sensor.set_bpc(&s_state->sensor, false);
        s_state->sensor.set_wpc(&s_state->sensor, true);
        s_state->sensor.set_lenc(&s_state->sensor, true);
    }

    if (pix_format == PIXFORMAT_JPEG) {
        s_state->sensor.set_quality(&s_state->sensor, config->jpeg_quality);
    }
    s_state->sensor.init_status(&s_state->sensor);

    cam_start();

    return ESP_OK;

fail:
    esp_camera_deinit();
    return err;
}

esp_err_t esp_camera_deinit()//esp_err_t esp_camera_deinit();
{
    esp_err_t ret = cam_deinit();
    CAMERA_DISABLE_OUT_CLOCK();
    if (s_state) {
        SCCB_Deinit();

        free(s_state);
        s_state = NULL;
    }

    return ret;
}

camera_fb_t *esp_camera_fb_get()//camera_fb_t* esp_camera_fb_get();
{
    if (s_state == NULL) {
        return NULL;
    }
    camera_fb_t *fb = cam_take(FB_GET_TIMEOUT);
    //set the frame properties
    if (fb) {
        fb->width = resolution[s_state->sensor.status.framesize].width;
        fb->height = resolution[s_state->sensor.status.framesize].height;
        fb->format = s_state->sensor.pixformat;
    }
    return fb;
}

void esp_camera_fb_return(camera_fb_t *fb)//void esp_camera_fb_return(camera_fb_t * fb);
{
    if (s_state == NULL) {
        return;
    }
    cam_give(fb);
}

sensor_t *esp_camera_sensor_get()//sensor_t * esp_camera_sensor_get();
{
    if (s_state == NULL) {
        return NULL;
    }
    return &s_state->sensor;
}

esp_err_t esp_camera_save_to_nvs(const char *key)//esp_err_t esp_camera_save_to_nvs(const char *key);
{
#if ESP_IDF_VERSION_MAJOR > 3
    nvs_handle_t handle;
#else
    nvs_handle handle;
#endif
    esp_err_t ret = nvs_open(key, NVS_READWRITE, &handle);

    if (ret == ESP_OK) {
        sensor_t *s = esp_camera_sensor_get();
        if (s != NULL) {
            ret = nvs_set_blob(handle, CAMERA_SENSOR_NVS_KEY, &s->status, sizeof(camera_status_t));
            if (ret == ESP_OK) {
                uint8_t pf = s->pixformat;
                ret = nvs_set_u8(handle, CAMERA_PIXFORMAT_NVS_KEY, pf);
            }
            return ret;
        } else {
            return ESP_ERR_CAMERA_NOT_DETECTED;
        }
        nvs_close(handle);
        return ret;
    } else {
        return ret;
    }
}

esp_err_t esp_camera_load_from_nvs(const char *key)//esp_err_t esp_camera_load_from_nvs(const char *key);
{
#if ESP_IDF_VERSION_MAJOR > 3
    nvs_handle_t handle;
#else
    nvs_handle handle;
#endif
    uint8_t pf;

    esp_err_t ret = nvs_open(key, NVS_READWRITE, &handle);

    if (ret == ESP_OK) {
        sensor_t *s = esp_camera_sensor_get();
        camera_status_t st;
        if (s != NULL) {
            size_t size = sizeof(camera_status_t);
            ret = nvs_get_blob(handle, CAMERA_SENSOR_NVS_KEY, &st, &size);
            if (ret == ESP_OK) {
                s->set_ae_level(s, st.ae_level);
                s->set_aec2(s, st.aec2);
                s->set_aec_value(s, st.aec_value);
                s->set_agc_gain(s, st.agc_gain);
                s->set_awb_gain(s, st.awb_gain);
                s->set_bpc(s, st.bpc);
                s->set_brightness(s, st.brightness);
                s->set_colorbar(s, st.colorbar);
                s->set_contrast(s, st.contrast);
                s->set_dcw(s, st.dcw);
                s->set_denoise(s, st.denoise);
                s->set_exposure_ctrl(s, st.aec);
                s->set_framesize(s, st.framesize);
                s->set_gain_ctrl(s, st.agc);
                s->set_gainceiling(s, st.gainceiling);
                s->set_hmirror(s, st.hmirror);
                s->set_lenc(s, st.lenc);
                s->set_quality(s, st.quality);
                s->set_raw_gma(s, st.raw_gma);
                s->set_saturation(s, st.saturation);
                s->set_sharpness(s, st.sharpness);
                s->set_special_effect(s, st.special_effect);
                s->set_vflip(s, st.vflip);
                s->set_wb_mode(s, st.wb_mode);
                s->set_whitebal(s, st.awb);
                s->set_wpc(s, st.wpc);
            }
            ret = nvs_get_u8(handle, CAMERA_PIXFORMAT_NVS_KEY, &pf);
            if (ret == ESP_OK) {
                s->set_pixformat(s, pf);
            }
        } else {
            return ESP_ERR_CAMERA_NOT_DETECTED;
        }
        nvs_close(handle);
        return ret;
    } else {
        ESP_LOGW(TAG, "Error (%d) opening nvs key \"%s\"", ret, key);
        return ret;
    }
}



