/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ResourceManager.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <stdexcept>

namespace RType {
    /**
     * @brief Classe pour gérer les resources comme les textures et les sons.
     */
    class ResourceManager {
    public:
        ResourceManager() = default;
        ~ResourceManager() = default;

        /**
         * @brief Charge une texture à partir d'un fichier.
         * @param name Nom associé à la texture.
         * @param filename Chemin du fichier de la texture.
         * @throw std::runtime_error Si le fichier de texture ne peut pas être chargé.
         */
        void loadTexture(const std::string& name, const std::string& filename) {
            sf::Texture texture;
            if (!texture.loadFromFile(filename)) {
                throw std::runtime_error("Failed to load texture from file: " + filename);
            }
            textures[name] = std::move(texture);
        }

        /**
         * @brief Charge un son à partir d'un fichier.
         * @param name Nom associé au son.
         * @param filename Chemin du fichier du son.
         * @throw std::runtime_error Si le fichier de son ne peut pas être chargé.
         */
        void loadSound(const std::string& name, const std::string& filename) {
            sf::SoundBuffer sound;
            if (!sound.loadFromFile(filename)) {
                throw std::runtime_error("Failed to load sound from file: " + filename);
            }
            sounds[name] = std::move(sound);
        }

        /**
         * @brief Charge une police : "font" à partir d'un fichier.
         * @param name Nom associé à la police.
         * @param filename Chemin du fichier de la font.
         * @throw std::runtime_error Si le fichier ne peut pas être chargé.
         */

        void loadFont(const std::string& name, const std::string& filename) {
            sf::Font font;
            if (!font.loadFromFile(filename)) {
                throw std::runtime_error("Failed to load font from file: " + filename);
            }
            fonts[name] = std::move(font);
        }

        /**
         * @brief Obtient une texture par son nom.
         * @param name Nom de la texture.
         * @return Référence à la texture demandée.
         * @throw std::out_of_range Si la texture n'est pas trouvée.
         */
        sf::Texture& getTexture(const std::string& name){
            return textures.at(name);
        }

        /**
         * @brief Obtient un son par son nom.
         * @param name Nom du son.
         * @return Référence au SoundBuffer demandé.
         * @throw std::out_of_range Si le son n'est pas trouvé.
         */
        sf::SoundBuffer& getSound(const std::string& name){
            return sounds.at(name);
        }

        /**
         * @brief Obtient une police par son nom.
         * @param name Nom de la police.
         * @return Référence à la police demandée.
         * @throw std::out_of_range Si la police n'est pas trouvée.
         */
        sf::Font& getFont(const std::string& name){
            return fonts.at(name);
        }

    private:
        std::map<std::string, sf::Texture> textures;
        std::map<std::string, sf::SoundBuffer> sounds;
        std::map<std::string, sf::Font> fonts;
    };

}
