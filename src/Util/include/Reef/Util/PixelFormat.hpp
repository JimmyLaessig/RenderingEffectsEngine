namespace Reef::Util
{

enum class PixelFormat
{
    // Uncompressed single channel (8-bit per channel)
    R_8,
    // Uncompressed two channels (8-bit per channel)
    RG_8,
    // Uncompressed three channels (8-bit per channel)
    RGB_8,
    // Uncompressed four channels (8-bit per channel)
    RGBA_8,

    // Uncompressed single channel (16-bit per channel)
    R_16,
    // Uncompressed two channels (16-bit per channel)
    RG_16,
    // Uncompressed three channels (16-bit per channel)
    RGB_16,
    // Uncompressed four channels (16-bit per channel)
    RGBA_16,

    // Uncompressed single channel floating point (32-bit per channel)
    R_32F,
    // Uncompressed single channel floating point (32-bit per channel)
    RGBA_32F,
}; // enum class PixelFormat


} // namespace Reef::Util
