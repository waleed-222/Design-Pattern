#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Font {
public:
    Font(const std::string& fontName, const std::string& fontStyle, int fontSize)
        : fontName(fontName), fontStyle(fontStyle), fontSize(fontSize) {}

    void display(const std::string& character, int x, int y) {
        std::cout << "Character: " << character << " at (" << x << "," << y << ") with Font: "
                  << fontName << ", Size: " << fontSize << ", Style: " << fontStyle << std::endl;
    }

private:
    int fontSize;
    std::string fontName;
    std::string fontStyle;
};

class FontFactory {
public:
    std::shared_ptr<Font> getFonts(const std::string& name, const std::string& style, int size) {
        std::string key = name + "_" + std::to_string(size) + "_" + style;
        if (fonts.find(key) == fonts.end()) {
            std::cout << "Creating new Font: " << key << std::endl;
            fonts[key] = std::make_shared<Font>(name, style, size);
        } else {
            std::cout << "Reusing existing Font: " << key << std::endl;
        }
        return fonts[key];
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Font>> fonts;
};

class Character {
public:
    Character(char value, int x, int y, std::shared_ptr<Font> font)
        : value(value), x(x), y(y), font(font) {}

    void display() const{
        font->display(std::string(1, value), x, y);
    }

private:
    char value;
    int x, y;
    std::shared_ptr<Font> font;
};

class Document {
public:
    void addCharacter(char value, int x, int y, const std::string& fontName,
                      const std::string& fontStyle, int fontSize) {
        auto font = fontFactory.getFonts(fontName, fontStyle, fontSize);
        characters.emplace_back(value, x, y, font);
    }

    void display() {
        for (const auto& character : characters)
            character.display();
    }

private:
    FontFactory fontFactory;
    std::vector<Character> characters;
};

int main() {
    Document doc;

    // Adding characters with the same font (flyweight reuse)
    doc.addCharacter('H', 10, 20, "Arial", "Bold", 12);
    doc.addCharacter('e', 20, 20, "Arial", "Bold", 12);
    doc.addCharacter('l', 30, 20, "Arial", "Bold", 12);
    doc.addCharacter('l', 40, 20, "Arial", "Bold", 12);
    doc.addCharacter('o', 50, 20, "Arial", "Bold", 12);

    // Adding different fonts
    doc.addCharacter('W', 60, 40, "TimesNewRoman", "Italic", 14);
    doc.addCharacter('o', 70, 40, "TimesNewRoman", "Italic", 14);
    doc.addCharacter('r', 80, 40, "TimesNewRoman", "Italic", 14);
    doc.addCharacter('l', 90, 40, "TimesNewRoman", "Italic", 14);
    doc.addCharacter('d', 100, 40, "TimesNewRoman", "Italic", 14);

    // Display the document
    doc.display();

    return 0;
}
