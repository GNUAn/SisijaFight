import os
import json
from PyQt6.QtWidgets import QApplication, QMainWindow, QTreeWidget, QTreeWidgetItem, QVBoxLayout, QWidget, QPushButton, QLineEdit, QFileDialog, QHBoxLayout
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QFont
import re

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Translations Finder")
        
        self.font = QFont()
        self.font.setPointSize(14)
        
        self.language_field = QLineEdit("de")
        self.loaded_translations = {}
        self.current_json_file = ""

        self.tree = QTreeWidget()
        self.tree.setHeaderLabels(["Original Text", "Translation"])

        self.load_translations()

        # Horizontales Layout für die Knöpfe und das Eingabefeld
        button_layout = QHBoxLayout()

        load_button = QPushButton("Load JSON")
        load_button.clicked.connect(self.load_from_json)

        save_button = QPushButton("Save to JSON")
        save_button.clicked.connect(self.save_to_json)

        rescan_button = QPushButton("Rescan Translations")
        rescan_button.clicked.connect(self.rescan_translations)

        button_layout.addWidget(self.language_field)
        button_layout.addWidget(load_button)
        button_layout.addWidget(save_button)
        button_layout.addWidget(rescan_button)

        # Vertikales Hauptlayout
        layout = QVBoxLayout()
        layout.addLayout(button_layout)
        layout.addWidget(self.tree)

        container = QWidget()
        container.setLayout(layout)
        self.setCentralWidget(container)
        self.tree.setFont(self.font)
        
    def resizeEvent(self, event):
        super().resizeEvent(event)
        if self.tree:
            self.tree.setColumnWidth(0, self.tree.width() // 2)  # Aktualisiere die Breite bei Größenänderung

    def rescan_translations(self):
        self.load_translations()

    def load_translations(self):
        for root, dirs, files in os.walk("."):
            for file in files:
                if file.endswith((".cpp", ".c", ".h", ".hpp")):
                    self.parse_file(os.path.join(root, file))

    def parse_file(self, file_path):
        try:
            with open(file_path, "r", encoding="utf-8") as file:
                lines = file.readlines()
                for line in lines:
                    for match in re.finditer(r'translate\("([^"]*)"\)', line):
                        original_text = match.group(1)
                        if original_text not in self.loaded_translations:
                            self.add_translation_item(original_text)
                            self.loaded_translations[original_text] = ""
        except UnicodeDecodeError:
            print(f"Warnung: Datei {file_path} konnte nicht gelesen werden (falsche Kodierung).")

    def add_translation_item(self, original_text, translation=""):
        item = QTreeWidgetItem([original_text, translation])
        item.setFlags(item.flags() | Qt.ItemFlag.ItemIsEditable)
        self.tree.addTopLevelItem(item)

    def load_from_json(self):
        file_name, _ = QFileDialog.getOpenFileName(self, "Open JSON File", "", "JSON Files (*.json)")
        if file_name:
            self.current_json_file = file_name
            with open(file_name, "r", encoding="utf-8") as file:
                new_translations = json.load(file)

            for original, translation in new_translations.items():
                found = False
                for i in range(self.tree.topLevelItemCount()):
                    item = self.tree.topLevelItem(i)
                    if item.text(0) == original:
                        item.setText(1, translation)
                        found = True
                        break

                if not found:
                    self.add_translation_item(original, translation)

    def save_to_json(self):
        if not self.current_json_file:
            self.current_json_file, _ = QFileDialog.getSaveFileName(self, "Save JSON", f"{self.language_field.text()}.json", "JSON Files (*.json)")

        for index in range(self.tree.topLevelItemCount()):
            item = self.tree.topLevelItem(index)
            original = item.text(0)
            translation = item.text(1)
            self.loaded_translations[original] = translation

        with open(self.current_json_file, "w", encoding="utf-8") as file:
            json.dump(self.loaded_translations, file, indent=4, ensure_ascii=False)

        print(f"Translations saved to {self.current_json_file}.")

app = QApplication([])
window = MainWindow()
app.setStyle("Fusion")
window.show()
app.exec()
