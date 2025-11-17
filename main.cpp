#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <cstddef>


template <typename T>

class GenericArray{
  static_assert(std::is_arithmetic<T>::value, "GenericArray<T> requires a numeric type (int, float, double, etc).");

  private:
    T* data_;
    std::size_t size_;

  public:
    //Constructor
    GenericArray() : data_(nullptr), size_(0) {}

    //Destructor
    ~GenericArray() {
      delete[] data_;
    }

    //Add to array
    void addElement(T value) {
      T* newData = new T[size_ + 1];
      for (std::size_t i = 0; i < size_; ++i) {
        newData[i] = data_[i];
      }
      newData[size_] = value;

      delete[] data_;
      data_ = newData;
      ++size_;
    }

    //Return value at index
    T at(int index) const {
      if (index < 0 || static_cast<std::size_t>(index) >= size_)
        throw std::out_of_range("Index out of range of array.");
      return data_[index];
    }

    //Return the size of the array
    std::size_t size() const {
      return size_;
    }

    //Return sum of the array
    T sum() const {
      T total = 0;
      for (std::size_t i = 0; i < size_; ++i) {
        total += data_[i];
      }
      return total;
    }

    //Return max value
    T max() const {
      if (size_ == 0) 
        throw std::runtime_error("Array is empty.");
      T maxVal = data_[0];
      for (std::size_t i = 1; i < size_; ++i)
        if (data_[i] > maxVal) maxVal = data_[i];
      return maxVal;
    }

    //Return minimum value
    T min() const {
      if (size_ == 0)
        throw std::runtime_error("Array is empty.");
      T minVal = data_[0];
      for (std::size_t i = 1; i < size_; ++i)
        if (data_[i] < minVal) minVal = data_[i];
      return minVal;
    }

    //Slice array
    T* slice(int begin, int end) const {
      if (begin < 0 || end < 0 || begin > end || static_cast<std::size_t>(end) >= size_) {
        throw std::out_of_range("Can not slice at current points (out of range).");
      }

      std::size_t length = end - begin + 1;
      T* newArray = new T[length];
      for (std::size_t i = 0; i < length; ++i) {
        newArray[i] = data_[begin + i];
      }
      return newArray;
    }
};

//Print array
template <typename T>
void printArray(const T* arr, std::size_t length) {
  std::cout << "[";
  for (std::size_t i = 0; i < length; ++i) {
    std::cout << arr[i];
    if (i < length - 1) std::cout << ", ";
  }
  std::cout << "]";
}

int main() {
  try {
    GenericArray<int> int_array;

    int n;
    std::cout << "Enter the size of the array: ";
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
      int value;
      std::cout << "Enter value " << i + 1 << ": ";
      std::cin >> value;
      int_array.addElement(value);
    }

    std::cout << "\nSize of array is " << int_array.size() << std::endl;
    std::cout << "Sum of array is " << int_array.sum() << std::endl;
    std::cout << "Maximum and minimum of the array are " << int_array.max() << " and " << int_array.min() << std::endl;

    int begin, end;
    std::cout << "\nEnter index for the start of the array slice: ";
    std::cin >> begin;
    std::cout << "Enter index for the end of the array slice: ";
    std::cin >> end;

    int* sliced_array = int_array.slice(begin, end);
    std::size_t sliceLength = end - begin + 1;

    std::cout << "\nSliced array (" << begin << " to " << end << "): ";
    printArray(sliced_array, sliceLength);
    std::cout << std::endl;

    delete[] sliced_array; //Clear memory
  }

  catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
