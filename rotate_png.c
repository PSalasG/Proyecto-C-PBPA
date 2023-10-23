#include "rotate_png.h"

void rotate_png(FILE *in_img, FILE *out_img) {
    png_structp leer_png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_r = png_create_info_struct(leer_png);
    png_init_io(leer_png, in_img);
    png_read_info(leer_png, info_r);

    png_structp w_png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop w_info = png_create_info_struct(w_png);
    png_init_io(w_png, out_img);

    png_uint_32 width, height;
    int bit_depth, color_type, interlace_method, compression_type, filter_method;
    png_get_IHDR(leer_png, info_r, &width, &height, &bit_depth, &color_type, &interlace_method, &compression_type, &filter_method);
    png_set_IHDR(w_png, w_info, height, width, bit_depth, color_type, interlace_method, compression_type, filter_method);
    png_write_info(w_png, w_info);

    png_bytepp row_pointers_original = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (int i = 0; i < height; i++) {
        row_pointers_original[i] = (png_byte*)malloc(png_get_rowbytes(leer_png, info_r));
    }
    png_read_image(leer_png, row_pointers_original);

    png_bytepp row_pointers_new = (png_bytep*)malloc(sizeof(png_bytep) * width);
    for (int i = 0; i < width; i++) {
        row_pointers_new[i] = (png_byte*)malloc(png_get_rowbytes(w_png, w_info));
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            row_pointers_new[i][j] = row_pointers_original[j][width - i - 1];
        }
    }

    png_write_image(w_png, row_pointers_new);

    for (int i = 0; i < width; i++) {
        free(row_pointers_new[i]);
    }
    free(row_pointers_new);

    for (int i = 0; i < height; i++) {
        free(row_pointers_original[i]);
    }
    free(row_pointers_original);

    png_write_end(w_png, w_info);
    png_destroy_read_struct(&leer_png, &info_r, NULL);
    png_destroy_write_struct(&w_png, &w_info);

}
