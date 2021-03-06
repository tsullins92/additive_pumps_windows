/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "CSVRow.h"
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}   

std::string const& CSVRow::operator[](std::size_t index) const
{
    return m_line_vector[index];
}

std::size_t CSVRow::size() const
{
    return m_line_vector.size();
}
        
std::vector<std::string> CSVRow::get_recipe_vector()
{
    return m_recipes_vector;
}

std::vector<std::string> CSVRow::get_values_vector(int recipes_index)
{
    return m_values_vector[recipes_index];
}

void CSVRow::readNextRow(std::istream& str)
{
    std::string         line;
    std::getline(str, line);
    std::stringstream   lineStream(line);
    std::string         cell;

    m_line_vector.clear();
    while(std::getline(lineStream, cell, ','))
    {
        m_line_vector.push_back(cell);
    }
    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty())
    {
        // If there was a trailing comma then add an empty element.
        m_line_vector.push_back("");
    }
    
}

void CSVRow::getRecipes()
{   
std::ifstream       file("recipes.csv");
CSVRow              row;
    while(file >> row)
    {

        m_recipes_vector.push_back(row[0]);
        m_values_vector.push_back({row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[10]});
    }
}

void CSVRow::edit_recipe(std::vector<std::string> recipe_info, int recipes_index)
{
    m_values_vector[recipes_index] = recipe_info;
    std::ofstream               output_file;
    output_file.open("recipes.csv");    //open file
    for (int i=0;i<m_recipes_vector.size();++i)
    {
        output_file << m_recipes_vector[i];
        for(int x=0;x<m_values_vector[i].size();++x)
        {
            if(!isalpha(m_values_vector[i][x][0]))                           //make sure that we are only writing numerical values to recipes.csv
            {
                output_file << "," << m_values_vector[i][x];
            }
        }
        output_file << "\n";
    }               
}




void CSVRow::write_recipe(std::vector<std::string> recipe_info)
{
    std::ofstream               output_file;
    output_file.open("recipes.csv", std::ios_base::app);    //open file in append mode
    output_file << "\n";
    for (int i=0;i<recipe_info.size();++i)
    {
        char value_check = recipe_info[i][0];
        if(!isalpha(value_check))                           //make sure that we are only writing numerical values to recipes.csv
        {
            output_file << recipe_info[i];
            if(i<(recipe_info.size()-1))   
            {
                output_file << ",";
            }
        }
    }               
}

