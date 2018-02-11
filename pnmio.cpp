////////////////////////////////////////////////////////////////////////////////
//
//  Author:         Ibrahim Sardar
//  Class:          CSCI 557
//  Filename:       pnmio.cpp
//  Date:           02/04/2018
//  Description:    Main implementation for PNM IO (read/write) class.
//
////////////////////////////////////////////////////////////////////////////////
//
//  Honor Pledge:
//
//  I pledge that I have neither given nor received any help on this project.
//
//  ibsardar
//
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2018 Copyright Holder All Rights Reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "pnmio.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <sstream>

//
//  bin_to_int
//
unsigned int pnmio::bin_to_uint(char c) {

    // place binary character byte into a bitset
    std::bitset<8> binary(c);
    return (unsigned int)(binary.to_ulong());
}

//
//  char_to_int
//
unsigned int pnmio::str_to_uint(std::string s) {

    // use a string-stream to get appropriate int value
    std::stringstream ss(s);
    unsigned int i;
    ss >> i;
    return i;
}

std::string pnmio::str_until_space(std::ifstream &ifs) {

    // only stop getting chars if eof, newline, or space is encountered
    std::string out = "";
    while (ifs.peek() && ifs.peek() != '\n' && ifs.peek() != ' ') {
        out.push_back(ifs.get());
    }
    return out;
}

//
//  load_image
//
Image pnmio::load_image(std::string fp, bool report, bool has_comment) {

    // open binary mode
    std::ifstream ifs(fp.c_str(), std::ios::binary|std::ios::in);

    // abort if failed to open
    if (!ifs) throw read_failure_exception(fp);

    // create empty Image structure
    Image img;

    // create empty (temporary) magic number array
    unsigned char mn[2];

    // create empty (temporary) dimensions array
    unsigned int dim[2];

    // create nil (temporary) max rgb magnitude
    unsigned int max_value = 0;

    // create a string that is used to ignore lines
    std::string ignore_text = "";

    // get magick number
    mn[0] = ifs.get();
    mn[1] = ifs.get();

    // assert format: 'P5' or 'P6'
    if (mn[0] != 'P' && (mn[1] == '5' || mn[1] == '6')) // Grayscale or RGB only
        throw read_failure_exception(fp);

    // next line
    ifs.get();

    // skip comment line
    if (has_comment)
        std::getline(ifs, ignore_text);

    // get image dimensions
    dim[0] = str_to_uint(str_until_space(ifs)); //width
    ifs.get(); // skip space character
    dim[1] = str_to_uint(str_until_space(ifs)); // height

    // next line
    ifs.get();

    // get max rgb/greyscale magnitude
    max_value = str_to_uint(str_until_space(ifs));

    // next line
    ifs.get();

    // calculate amount of expected data values
    int amt = dim[0] * dim[1];
    if (mn[1] == '6') amt *= 3; // 3x more data for RGB than Grayscale

    // gather data
    int cntr = 0;
    while (cntr < amt) {
        cntr++;
        img.data.push_back(bin_to_uint(ifs.get())); // gather data
    }

    // closes the filestream
    ifs.close();

    // print data info
    if (report) {
        std::cout << "\n--- PNM Read Report:" << '\n';
        std::cout << "\tType: " << mn[0] << mn[1] << '\n';
        std::cout << "\tWidth: " << dim[0] << '\n';
        std::cout << "\tHeight: " << dim[1] << '\n';
        std::cout << "\tMax Data Point Value: " << max_value << '\n';
        std::cout << "\tData Point Value Matrix:";
        int col_elems = (mn[1] == '6') ? dim[0]*3 : dim[0];
        for (unsigned int i=0; i<amt; i++) {
            int row = i / col_elems; // first row is = to 0
            int col = i % col_elems; // first column is = to 0

            if (col == 0) std::cout << '\n' << '\t' << '\t';
            std::cout << img.data[i];
            if (col != col_elems - 1) std::cout << ',';
        }
        std::cout << "\n--------------------" << std::endl;
    }

    // construct and return the Image structure
    img.type = (mn[1] == '6') ? 1 : 0; //type
    img.width = dim[0]; //width
    img.height = dim[1]; //height
    img.max_val = max_value; //max data point value
    return img;
}

//
// store_image
//
void pnmio::store_image(std::string fp, Image &img) {

    //...
}
