/*
* MIT License
*
* Copyright (c) 2018 Denis Rozhkov <denis@rozhkoff.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "stdafx.h"


int main()
{
	Aws::SDKOptions options;
    options.monitoringOptions.customizedMonitoringFactory_create_fn = std::vector<Aws::Monitoring::MonitoringFactoryCreateFunction>();
    try {
        Aws::InitAPI(options);
    }
    catch (const std::exception & x) {
            std::cerr << x.what() << std::endl;
        }
        catch (...) {
            std::cerr << "error" << std::endl;
        }
	try {
		std::string regionId = "us-west-2";
		std::string clientId = "";
		std::string username = "";
		std::string password = "";
		std::string userPoolId = "";		// without region
		std::string identityPoolId = "";	// without region

		awsx::CognitoAuth auth( regionId, clientId );
        auto token = auth.GetTokens(username, password, userPoolId);
        std::cout << "Tokens Expire in: " << token.GetExpiresIn() << std::endl;
        std::cout << std::endl;
        if (token.AccessTokenHasBeenSet()) {
            std::cout << "Access Token: " << token.GetAccessToken() << std::endl;
        }
        else {
            std::cout << "No Access Token" << std::endl;
        }
        std::cout << std::endl;
        if (token.IdTokenHasBeenSet()) {
            std::cout << "Id Token: " << token.GetIdToken() << std::endl;
        }
        else {
            std::cout << "No ID Token" << std::endl;
        }
        std::cout << std::endl;

        if (token.RefreshTokenHasBeenSet()) {
            std::cout << "Refresh Token: " << token.GetRefreshToken() << std::endl;
        }
        else {
            std::cout << "No Refresh Token" << std::endl;
        }
        _sleep(10000);
        std::cout << std::endl << "Doing token Refresh"<<std::endl;
        token = auth.RefreshTokens(token.GetRefreshToken());
        //token = auth.GetTokens(username, password, userPoolId);

        std::cout << "Tokens Expire in: " << token.GetExpiresIn() << std::endl;
        if (token.AccessTokenHasBeenSet()) {
            std::cout << "Access Token: " << token.GetAccessToken() << std::endl;
        }
        else {
            std::cout << "No Access Token" << std::endl;
        }
        if (token.IdTokenHasBeenSet()) {
            std::cout << "Id Token: " << token.GetIdToken() << std::endl;
        }
        else {
            std::cout << "No ID Token" << std::endl;
        }
        if (token.RefreshTokenHasBeenSet()) {
            std::cout << "Refresh Token: " << token.GetRefreshToken() << std::endl;
        }
        else {
            std::cout << "No Refresh Token" << std::endl;
        }


        
        auto creds = auth.Authenticate(username, password, userPoolId, identityPoolId);
        if (!creds.GetAWSAccessKeyId().empty()) {
            std::cout << "access key = " << creds.GetAWSAccessKeyId() << std::endl;
        }

	}
	catch (const std::exception & x) {
		std::cerr << x.what() << std::endl;
	}
	catch (...) {
		std::cerr << "error" << std::endl;
	}

	Aws::ShutdownAPI( options );

	return 0;
}
