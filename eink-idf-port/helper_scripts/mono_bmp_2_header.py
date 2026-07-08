#!/usr/bin/env python3
"""Convert a monochrome (1-bit) BMP/PNG image to a C header with a byte array.

Usage: mono_bmp_2_header.py input.png [-o out.h] [-n name]
"""
from PIL import Image
import argparse
import os
import sys


def pack_image(img: Image.Image) -> bytes:
	# ensure 1-bit pixels, black=0, white=1
	if img.mode != "1":
		img = img.convert("1")
	w, h = img.size
	pixels = img.tobytes()
	packed = bytearray()
	for y in range(h):
		byte = 0
		bit_count = 0
		for x in range(w):
			# get pixel value (0 or 255)
			v = img.getpixel((x, y))
			bit = 0 if v else 1  # treat black (0) as 1 in bitmap (set bit), white as 0
			byte = (byte << 1) | (bit & 1)
			bit_count += 1
			if bit_count == 8:
				packed.append(byte)
				byte = 0
				bit_count = 0
		if bit_count != 0:
			# pad remaining bits on the right
			byte = byte << (8 - bit_count)
			packed.append(byte)
	return bytes(packed)


def make_c_header(image_path: str, out_path: str, name: str):
	img = Image.open(image_path)
	w, h = img.size
	data = pack_image(img)
	guard = os.path.basename(out_path).upper().replace('.', '_').replace('-', '_') + '_'
	array_name = name

	with open(out_path, 'w', newline='\n') as f:
		f.write(f"#ifndef {guard}\n")
		f.write(f"#define {guard}\n\n")
		f.write(f"// Generated from: {os.path.basename(image_path)}\n")
		f.write(f"const unsigned int {array_name}_width = {w};\n")
		f.write(f"const unsigned int {array_name}_height = {h};\n")
		f.write(f"const unsigned char {array_name}_data[] = {{\n")
		for i, b in enumerate(data):
			if i % 12 == 0:
				f.write("    ")
			f.write(f"0x{b:02X}")
			if i != len(data) - 1:
				f.write(", ")
			if (i + 1) % 12 == 0:
				f.write("\n")
		f.write("\n};\n\n")
		f.write(f"#endif // {guard}\n")


def main():
	p = argparse.ArgumentParser()
	p.add_argument('input', help='input image (BMP/PNG)')
	p.add_argument('-o', '--output', help='output header file', default=None)
	p.add_argument('-n', '--name', help='base name for symbols', default='bitmap')
	args = p.parse_args()
	inp = args.input
	out = args.output or (os.path.splitext(os.path.basename(inp))[0] + '.h')
	make_c_header(inp, out, args.name)


if __name__ == '__main__':
	main()
