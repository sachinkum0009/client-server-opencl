#include "../include/cl_code.hpp"

ClCode::ClCode() {
	cl::Platform::get(&all_platforms);
    if(all_platforms.size()==0){
        std::cout<<" No platforms found. Check OpenCL installation!\n";
        exit(1);
    }
	std::cout << "size of platforms " << all_platforms.size() << std::endl;
    cl::Platform default_platform=all_platforms[0];
    std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";
 
    //get default device of the default platform
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if(all_devices.size()==0){
        std::cout<<" No devices found. Check OpenCL installation!\n";
        exit(1);
    }
    cl::Device default_device=all_devices[0];
    std::cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";
 
 
    cl::Context context({default_device});
 
    cl::Program::Sources sources;
 
    std::string kernel_code=
            "   void kernel compare_distance(global const int* distance, global const int* safetyDistance, global bool* status){       "
            // "       C[get_global_id(0)]=A[get_global_id(0)]-B[get_global_id(0)];                 "
			"		if(distance[get_global_id(0)] > safetyDistance[get_global_id(0)]){												"
			"			status[get_global_id(0)] = true;															"
			"		}																			"
			"		else {																		"
			"			status[get_global_id(0)] = true;															"
			"		}																			"
            "   }                                                                               ";
    sources.push_back({kernel_code.c_str(),kernel_code.length()});

    // void kernel simple_function(global const int*A, globa const int*B, global int*C) {
    //     C[get_global_id(0)]=A[get_global_id(0)]-B[get_global_id(0)]; 
    // }

 
    cl::Program program(context,sources);
    if(program.build({default_device})!=CL_SUCCESS){
        std::cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
        exit(1);
    }
 
 
    // create buffers on the device
    cl::Buffer buffer_A(context,CL_MEM_READ_WRITE,sizeof(int));
    cl::Buffer buffer_B(context,CL_MEM_READ_WRITE,sizeof(int));
    cl::Buffer buffer_C(context,CL_MEM_READ_WRITE,sizeof(bool));
 
    // int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // int B[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0};
	int distance = 100;
	int safetyDistance = 50;
 
    //create queue to which we will push commands for the device.
    cl::CommandQueue queue(context,default_device);
 
    //write arrays A and B to the device
    queue.enqueueWriteBuffer(buffer_A,CL_TRUE,0,sizeof(int),&distance);
    queue.enqueueWriteBuffer(buffer_B,CL_TRUE,0,sizeof(int),&safetyDistance);
 
 
    //run the kernel
    
    // cl::KernelFunctor simple_add(cl::Kernel(program,"simple_add"),queue,cl::NullRange,cl::NDRange(10),cl::NullRange);
    // simple_add(buffer_A,buffer_B,buffer_C);
 
    //alternative way to run the kernel
    cl::Kernel kernel_add=cl::Kernel(program,"simple_add");
    kernel_add.setArg(0,buffer_A);
    kernel_add.setArg(1,buffer_B);
    kernel_add.setArg(2,buffer_C);
    queue.enqueueNDRangeKernel(kernel_add,cl::NullRange,cl::NDRange(1),cl::NullRange);
    queue.finish();
 
    // int C[10];
	bool status = true;
    //read result C from the device to array C
    queue.enqueueReadBuffer(buffer_C,CL_TRUE,0,sizeof(bool),&status);
 
    std::cout<<" result: ";
    // for(int i=0;i<10;i++){
        std::cout<<status<<" ";
    // }
    std::cout << std::endl;
}
ClCode::~ClCode(){}

int main(int argc, char const *argv[])
{
	ClCode obj;
	return 0;
}
