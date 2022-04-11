// Workshop 9 - Multi-Threading, Thread Class
// process_data.cpp
// 2021/1/5 - Jeevan Pant


#include "process_data.h"

using namespace std::placeholders;
namespace sdds_ws9 {

	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++) {
			avg += arr[i];
		}
		avg /= divisor;
	}

	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++) {
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}
	ProcessData::operator bool() const {
		return total_items > 0 && data && num_threads>0 && averages && variances && p_indices;
	}

	ProcessData::ProcessData(std::string filename, int n_threads) {  
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.
		std::fstream file(filename,
			std::ios::in | std::ios::binary);
		if (!file)
		{
			std::cout << "File cannot be opened.";
		}

		file.read(reinterpret_cast<char*>(&total_items), sizeof(total_items));

		data = new int[total_items];
		int i = 0;
		while (!file.eof()) {
			//for (size_t i = 0; i < total_items; i++)
			//{
			file.read(reinterpret_cast<char*>(&data[i]), sizeof(data[i]));
			i++;
		}

		std::cout << "Item's count in file '"<< filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
		          << data[total_items - 3] << ", " << data[total_items - 2] << ", "
		          << data[total_items - 1] << "]\n";

		// Following statements initialize the variables added for multi-threaded 
		//   computation
		num_threads = n_threads; 
		averages = new double[num_threads] {};
		variances = new double[num_threads] {};
		p_indices = new int[num_threads+1] {};
		for (int i = 0; i < num_threads+1; i++)
			p_indices[i] = i * (total_items / num_threads);
	}
	ProcessData::~ProcessData() {
		delete[] data;
		delete[] averages;
		delete[] variances;
		delete[] p_indices;
	}

	// TODO Improve operator() function from part-1 for multi-threaded operation. Enhance the  
	//   function logic for the computation of average and variance by running the 
	//   function computeAvgFactor and computeVarFactor in multile threads. 
	// The function divides the data into a number of parts, where the number of parts is 
	//   equal to the number of threads. Use multi-threading to compute average-factor for 
	//   each part of the data by calling the function computeAvgFactor. Add the obtained 
	//   average-factors to compute total average. Use the resulting total average as the 
	//   average value argument for the function computeVarFactor, to compute variance-factors 
	//   for each part of the data. Use multi-threading to compute variance-factor for each 
	//   part of the data. Add computed variance-factors to obtain total variance.
	// Save the data into a file with filename held by the argument fname_target. 
	// Also, read the workshop instruction.
	int ProcessData::operator()(std::string fileName, double& avg, double& var) {

		//num_threads = 2;
		//averages = new double[num_threads];
		//variances = new double[num_threads];
		//p_indices = new int[num_threads];
		//p_indices[0] = data[0];
		//p_indices[1] = data[(total_items / num_threads) + 1];
		
		//avg_p = &averages[0];
		//p_indices = &data[0];

		//auto average = std::bind(computeAvgFactor, p_indices, total_items / num_threads, total_items, averages);

		std::vector<std::thread> avg_threads;
		std::vector<std::thread> var_threads;

		for (size_t i = 0; i < num_threads; i++)
		{
			//auto average = std::bind(computeAvgFactor, &data[p_indices[i]], total_items / num_threads, total_items, averages[i]);

			//avg_threads.push_back(std::thread(average));
			avg_threads.push_back(std::thread(std::bind(computeAvgFactor, &data[p_indices[i]] , total_items / num_threads, total_items, averages[i])));
			std::cout << data[p_indices[i]] << std::endl;
			std::cout << averages[i];
		}
		for (size_t i = 0; i < num_threads; i++)
		{
			avg += averages[i];
		}
		for (size_t i = 0; i < avg_threads.size(); i++)
		{
			avg_threads[i].join();
		}
		//--------------------------------------------------------------------------------------------------
		for (size_t i = 0; i < num_threads; i++)
		{
			auto variance = std::bind(computeVarFactor, &data[p_indices[i]], total_items / num_threads, total_items, avg, variances[i]);
			std::cout << variances[i];
			var_threads.push_back(std::thread(variance));
		}
		for (size_t i = 0; i < num_threads; i++)
		{
			var += variances[i];
		}
		for (size_t i = 0; i < avg_threads.size(); i++)
		{
			var_threads[i].join();
		}

		//avg = averages[0] + averages[1];

		//p_indices = &data[0];
		//avg_p = &averages[0];
		//std::thread t1(average);

		//p_indices = &data[(total_items / num_threads) + 1];
		//avg_p = &averages[1];
		//auto average2 = std::bind(computeAvgFactor, p_indices, total_items / num_threads, total_items, averages[1]);
		//::thread t2(average);
		/*auto average = std::bind(computeAvgFactor, data, _1, _2, _3);*/
		//auto variance = std::bind(computeVarFactor, data, _1, _2, avg, _3);

		
		
		//std::thread t1(computeAvgFactor, data[0], total_items / 2, total_items / 2, first_part);
		//std::thread t2(computeAvgFactor, data[(total_items / 2) + 1], total_items / 2, total_items / 2, second_part);





		//std::thread t3(computeVarFactor, data[0], total_items / 2, total_items / 2, avg, first_part);
		//std::thread t4(computeVarFactor, data[(total_items / 2) + 1], total_items / 2, total_items / 2, avg, second_part);

		//var = (first_part + second_part) / 2;

		//t1.join();
		//t2.join();
		//t3.join();
		//t4.join();
		//computeAvgFactor(data, total_items, total_items, avg);
		//computeVarFactor(data, total_items, total_items, avg, var);
		std::fstream file(fileName,
			std::ios::out | std::ios::binary);
		file.write(reinterpret_cast<char*>(&total_items), sizeof(total_items));
		int i = 0;
		while (i < total_items) {
			//for (size_t i = 0; i < total_items; i++)
			//{
			file.write(reinterpret_cast<char*>(&data[i]), sizeof(data[i]));
			i++;
		}
		return 0;
	}




}