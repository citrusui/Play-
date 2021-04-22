#pragma once

#include <string>
#include "amazon/AmazonS3Client.h"

namespace AmazonS3Utils
{
	ListObjectsResult GetListObjects(const CAmazonCredentials&, std::string);
};
