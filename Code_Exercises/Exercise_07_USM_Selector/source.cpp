/*
 SYCL Academy (c)

 SYCL Academy is licensed under a Creative Commons
 Attribution-ShareAlike 4.0 International License.

 You should have received a copy of the license along with this
 work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#if defined(SYCL_LANGUAGE_VERSION) && defined(__INTEL_LLVM_COMPILER)
#include <CL/sycl.hpp>
#else
#include <SYCL/sycl.hpp>
#endif

class usm_selector : public sycl::device_selector {
 public:
  int operator()(const sycl::device& dev) const {
    // write an if statement to check the device has USM support, 
	// see slide 10 for the parameter value
      return 1;
    }
    return -1;
  }
};

TEST_CASE("usm_selector", "usm_selector_source") {
  try {
    auto asyncHandler = [&](sycl::exception_list exceptionList) {
      for (auto& e : exceptionList) {
        std::rethrow_exception(e);
      }
    };

    // Set up a queue using the USM device selector
    // See Lesson 5 slide 17 for a hint, but also pass it 
    // the asyncHandler to catch any exceptions
    // Start with auto usmQueue = and set up your queue

    usmQueue.throw_asynchronous();
  } catch (const sycl::exception& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  REQUIRE(true);
}
