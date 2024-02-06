//
// Created by Anatta Feng on 2024/1/29.
//

#include "vgfx/utils/Stream.h"
#include "Logger.h"

namespace vgfx {
class FileStream : public Stream {
 public:
  FileStream(FILE *file, size_t length) : file(file), length(length) {

  }

  ~FileStream() override {
    fclose(file);
  }

  size_t size() const override {
    return length;
  }

  bool seek(size_t position) override {
    return fseek(file, static_cast<long >(position), SEEK_SET) == 0;
  }

  bool move(int offset) override {
    return fseek(file, offset, SEEK_CUR) == 0;
  }

  size_t read(void *buffer, size_t size) override {
    return fread(buffer, 1, size, file);
  }

  bool rewind() override {
    return fseek(file, 0, SEEK_SET) == 0;
  }

 private:
  FILE *file = nullptr;
  size_t length = 0;
};

std::unique_ptr<Stream> Stream::MakeFromFile(const std::string &filePath) {
  auto file = fopen(filePath.c_str(), "rb");
  if (file == nullptr) {
    LOGE("File open failed! File path: %s", filePath.c_str());
    return nullptr;
  }
  fseek(file, 0, SEEK_END);
  auto length = ftell(file);
  if (length <= 0) {
    fclose(file);
    return nullptr;
  }
  fseek(file, 0, SEEK_SET);
  return std::make_unique<FileStream>(file, length);
}
} // vgfx