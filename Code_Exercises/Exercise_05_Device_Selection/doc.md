# SYCL Academy

## Exercise 5: Device Selection

---

In this exercise you will learn how to create a device selector that will choose
a device for you to enqueue work to.

---

### 1.) Create your own device selector

Create a device selector using the template below, implementing the function
call operator, using various device and platform info queries like the one we
used earlier to query the device name and then use that device selector in the
queue constructor:

```
class my_device_selector : public device_selector {
 public:
  my_device_selector() {}

  virtual int operator()(const device &device) const { /* scoring logic */ }
};
```

Remember the platform associated with a device can be retrieved using the
`get_platform` member function.

Remember that the value returned from the device selector's function call
operator will represent the score for each device, and a device with a negative
score will never be chosen. 

#### Build And Execution Hints

For For DPC++ (using the Intel DevCloud):
```sh
dpcpp -o sycl-ex-5 -I../External/Catch2/single_include ../Code_Exercises/Exercise_05_Device_Selection/source.cpp
```
In Intel DevCloud, to run computational applications, you will submit jobs to a queue for execution on compute nodes,
especially some features like longer walltime and multi-node computation is only abvailable through the job queue.
Please refer to the [guide][devcloud-job-submission].

So wrap the binary into a script `job_submission` and run:
```sh
qsub job_submission
```

For ComputeCpp:
```sh
cmake -DSYCL_ACADEMY_USE_COMPUTECPP=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/computecpp ..
make exercise_05_device_selection_source
./Code_Exercises/Exercise_05_Device_Selection/exercise_04_handling_errors source
```


For hipSYCL:
```sh
# <target specification> is a list of backends and devices to target, for example
# "omp;hip:gfx900,gfx906" compiles for CPUs with the OpenMP backend and for AMD Vega 10 (gfx900) and Vega 20 (gfx906) GPUs using the HIP backend.
# The simplest target specification is "omp" which compiles for CPUs using the OpenMP backend.
cmake -DSYCL_ACADEMY_USE_HIPSYCL=ON -DSYCL_ACADEMY_INSTALL_ROOT=/insert/path/to/hipsycl -DHIPSYCL_TARGETS="<target specification>" ..
make exercise_05_device_selection_source
./Code_Exercises/Exercise_05_Device_Selection/exercise_05_device_selection_source
```
alternatively, without cmake:
```sh
cd Code_Exercises/Exercise_05_Device_Selection
/path/to/hipsycl/bin/syclcc -o sycl-ex-5 -I../../External/Catch2/single_include --hipsycl-targets="<target specification>" source.cpp
./sycl-ex-5
```


[devcloud-job-submission]: https://devcloud.intel.com/oneapi/documentation/job-submission/
