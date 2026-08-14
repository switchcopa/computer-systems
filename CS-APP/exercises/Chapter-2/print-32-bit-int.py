
def print_raw_bits_32(val: int):
    # Ensure the integer fits in 32-bit signed range (-2^31 to 2^31 - 1)
    if not (-2147483648 <= val <= 2147483647):
        raise ValueError("Value out of range for a signed 32-bit integer.")

    # Mask with 0xFFFFFFFF to get the exact 32-bit bit pattern (handles negative two's complement)
    bits_32 = val & 0xFFFFFFFF

    # Format as 32-character binary string zero-padded on the left
    bit_str = f"{bits_32:032b}"

    # Break into 4 byte chunks for readability
    byte_chunks = [bit_str[i : i + 8] for i in range(0, 32, 8)]
    formatted_bits = " ".join(byte_chunks)

    print(f"Decimal Value : {val}")
    print(f"Raw 32 Bits   : {formatted_bits}")
    print(f"                |        |        |")
    print(f"                Byte 3   Byte 2   Byte 1   Byte 0")
    print(f"                (MSB)                      (LSB)")
    print(f"Sign bit      : {bit_str[0]} ({'Negative' if bit_str[0] == '1' else 'Positive'})\n")

print_raw_bits_32(127)
print_raw_bits_32(-128)
