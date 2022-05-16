/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class scalar_add;

#if defined(SYCL_LANGUAGE_VERSION) && defined(__INTEL_LLVM_COMPILER)
#include <CL/sycl.hpp>
#else
#include <SYCL/sycl.hpp>
#endif

// Here you can define your device selector, if you are using the Docker image
// you can only use the CPU so should set up a CPU selector, if you are using 
// your own machine you could try the GPU selector, see slide 15 for example
// In the main body of the code you can find out what devices are on your machine 
// using code like this
// for (const auto cl::sycl::device& device : platform.get_devices() )
//   std::cout << " Name   : "
//                 << device.get_info< cl::sycl::info::device::name >();


TEST_CASE("intel_gpu_device_selector", "device_selectors_solution") {
  int a = 18, b = 24, r = 0;

  // Exception handling code
  try {
    auto asyncHandler = [&](sycl::exception_list exceptionList) {
      for (auto& e : exceptionList) {
        std::rethrow_exception(e);
      }
    };
    // set up the queue with the custom device selector
    auto defaultQueue = sycl::queue{my_selector{}, asyncHandler};

    // Print out the device that was chosen
    std::cout << "Chosen device: "
              << defaultQueue.get_device().get_info<sycl::info::device::name>()
              << std::endl;

    {
      auto bufA = sycl::buffer{&a, sycl::range{1}};
      auto bufB = sycl::buffer{&b, sycl::range{1}};
      auto bufR = sycl::buffer{&r, sycl::range{1}};

      // Submit the kernel 
      defaultQueue
          .submit([&](sycl::handler& cgh) {
            auto accA = sycl::accessor{bufA, cgh, sycl::read_only};
            auto accB = sycl::accessor{bufB, cgh, sycl::read_only};
            auto accR = sycl::accessor{bufR, cgh, sycl::write_only};

            cgh.single_task<scalar_add>([=]() { accR[0] = accA[0] + accB[0]; });
          })
          .wait();
    }

    defaultQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  REQUIRE(r == 42);
}
