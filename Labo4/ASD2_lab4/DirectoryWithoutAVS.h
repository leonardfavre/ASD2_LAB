//
//  DirectoryWithoutAVS.h
//  ASD2_2015
//
//  Created by Fabien Dutoit on 19.10.15.
//  Modified by: Favre Leonard, Girard Matthieu et Schranz Guillaume
//  Copyright © 2015 IICT, HEIG-VD. All rights reserved.
//

#ifndef DirectoryWithoutAVS_h
#define DirectoryWithoutAVS_h

#include <string>
#include <cctype>
#include <iostream>
#include <functional>

class DirectoryWithoutAVS {
private:
    std::string name;
    std::string firstname;
    std::string gender;
    std::string birthday;
    
public:
    DirectoryWithoutAVS();
    DirectoryWithoutAVS(std::string avs, /* SHOULD NOT BE USED */
                  std::string name,
                  std::string firstname,
                  std::string gender,
                  std::string birthday);
    
    std::string getName() const;
    std::string getFirstname() const;
    std::string getGender() const;
    std::string getBirthday() const;
    
    //operators
    bool operator ==(const DirectoryWithoutAVS &that) const;
    friend std::ostream& operator <<(std::ostream&, const DirectoryWithoutAVS&);
    
};

namespace std
{
    template <>
    struct hash<DirectoryWithoutAVS>
    {
        size_t operator()(const DirectoryWithoutAVS& d) const
        {   
            // On convertit le genre en int. M = 1, F = 0
            int genderInt = 0;
            if (d.getGender() == "M") genderInt = 1;
            
            // On convertit la date d'anniversaire en int, aussi.
            unsigned int birthdayInt;
            //convert string to long
            try {
                birthdayInt = std::atoi(d.getBirthday().c_str());
            } catch(std::out_of_range& e) {
                std::cerr << "Not a valid int: " << d.getBirthday() << std::endl;
                birthdayInt = 0; //default value
            }
            
            // Utilisation de la recette "standard" pour hasher un type défini par l'utilisateur
            size_t hashval = 17;
            hashval = 31 * hashval + hash<string>()(d.getName());
            hashval = 31 * hashval + hash<string>()(d.getFirstname());
            hashval = 31 * hashval + hash<int>()(birthdayInt);
            hashval = 31 * hashval + hash<int>()(genderInt);
            return hashval;            
        }
    };
}

#endif /* DirectoryWithoutAVS_h */
