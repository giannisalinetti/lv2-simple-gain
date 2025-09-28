#include <stdlib.h>
#include <string.h>
#include <lv2/core/lv2.h>

#define SIMPLE_GAIN_URI "http://github.com/giannisalinetti/lv2-simple-gain"

/* Port indices */
typedef enum {
    SIMPLE_GAIN_INPUT  = 0,
    SIMPLE_GAIN_OUTPUT = 1,
    SIMPLE_GAIN_GAIN   = 2
} PortIndex;

/* Plugin instance data */
typedef struct {
    /* Port buffers */
    const float* input;
    float*       output;
    const float* gain;
} SimpleGain;

/**
 * Instantiate the plugin.
 * This function is called by the host to create a new plugin instance.
 */
static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{
    SimpleGain* simple_gain = (SimpleGain*)malloc(sizeof(SimpleGain));
    if (!simple_gain) {
        return NULL;
    }

    /* Initialize all port pointers to NULL */
    simple_gain->input  = NULL;
    simple_gain->output = NULL;
    simple_gain->gain   = NULL;

    return (LV2_Handle)simple_gain;
}

/**
 * Connect a port to a buffer.
 * This function is called by the host to connect plugin ports to buffers.
 */
static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
    SimpleGain* simple_gain = (SimpleGain*)instance;

    switch ((PortIndex)port) {
    case SIMPLE_GAIN_INPUT:
        simple_gain->input = (const float*)data;
        break;
    case SIMPLE_GAIN_OUTPUT:
        simple_gain->output = (float*)data;
        break;
    case SIMPLE_GAIN_GAIN:
        simple_gain->gain = (const float*)data;
        break;
    }
}

/**
 * Run the plugin for a block of samples.
 * This is where the main audio processing happens.
 */
static void
run(LV2_Handle instance, uint32_t n_samples)
{
    SimpleGain* simple_gain = (SimpleGain*)instance;

    const float* const input  = simple_gain->input;
    float* const       output = simple_gain->output;
    const float        gain   = *(simple_gain->gain);

    /* Process each sample */
    for (uint32_t pos = 0; pos < n_samples; pos++) {
        output[pos] = input[pos] * gain;
    }
}

/**
 * Clean up the plugin instance.
 * This function is called by the host when the plugin instance is no longer needed.
 */
static void
cleanup(LV2_Handle instance)
{
    SimpleGain* simple_gain = (SimpleGain*)instance;
    free(simple_gain);
}

/**
 * Plugin descriptor.
 * This structure contains all the information the host needs about the plugin.
 */
static const LV2_Descriptor descriptor = {
    SIMPLE_GAIN_URI,
    instantiate,
    connect_port,
    NULL,  /* activate */
    run,
    NULL,  /* deactivate */
    cleanup,
    NULL   /* extension_data */
};

/**
 * Entry point for the plugin.
 * This function is called by the host to get plugin descriptors.
 */
LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
    switch (index) {
    case 0:
        return &descriptor;
    default:
        return NULL;
    }
}
