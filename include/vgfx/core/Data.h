//
// Created by Anatta Feng on 2024/1/25.
//

#pragma once

#include <memory>
#include <string>

namespace vgfx {

/**
 * Data holds an immutable data buffer. Not only is the Data immutable, but the actual pointer
 * returned by data() or bytes() is guaranteed to always be the same for the life of this instance.
 */
class Data {
 public:
  /**
   * Creates a Data object from the specified file path.
   * @param filePath
   * @return
   */
  static std::shared_ptr<Data> MakeFromFile(const std::string &filePath);

  /**
   * Creates a Data object by copying the specified data.
   * @param data
   * @param length
   * @return
   */
  static std::shared_ptr<Data> MakeWithCopy(const void *data, size_t length);

  /**
   * Call this when data parameter is already const, suitable for const globals. The caller must
   * ensure the data parameter will always be the same and alive for the lifetime of the returned
   * Data.
   * @param data
   * @param length
   * @return
   */
  static std::shared_ptr<Data> MakeWithoutCopy(const void *data, size_t length);

  /***
   * Function that, if provided, will be called when the Data goes out of scope, allowing for
   * custom allocation/freeing of the data's contents.
   */
  typedef void (*ReleaseProc)(const void *data, void *context);

  /**
   * A ReleaseProc using delete to release data.
   * @param data
   * @param context
   */
  static void DeleteProc(const void *data, void *context);

  /**
   * A ReleaseProc using free() to release data.
   * @param data
   * @param context
   */
  static void FreeProc(const void *data, void *context);

  /**
   * Creates a Data object, taking ownership of the specified data, and using the releaseProc to
   * free it. The releaseProc may be nullptr.
   * @param data
   * @param length
   * @param releaseProc
   * @param context
   * @return
   */
  static std::shared_ptr<Data> MakeAdopted(const void *data, size_t length,
                                           ReleaseProc releaseProc = DeleteProc,
                                           void *context = nullptr);

  /**
   * Creates a new empty Data object.
   * @return
   */
  static std::shared_ptr<Data> MakeEmpty();

  ~Data();

  /**
   * Returns the memory address of the data.
   * @return
   */
  const void *data() const {
    return _data;
  }

  /**
   * Returns the read-only memory address of the data, but in this case it is cast to uint8_t*, to
   * make it easy to add an offset to it.
   * @return
   */
  const uint8_t *bytes() const {
    return reinterpret_cast<const uint8_t *>(_data);
  }

  /**
   * Returns the byte size.
   * @return
   */
  size_t size() const {
    return _size;
  }

  /**
   * Returns true if the Data is empty.
   * @return
   */
  bool empty() const {
    return _size == 0;
  }

 private:
  const void *_data = nullptr;
  size_t _size = 0;
  ReleaseProc releaseProc = nullptr;
  void *releaseContext = nullptr;

  Data(const void *data, size_t length, ReleaseProc releaseProc, void *context);
};

} // vgfx