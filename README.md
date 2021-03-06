 
An Uptane Client Library in C

============================

  *With companion test application*

This software is Copyright (c) 2016 Sam Lauzon (slauzon at umich.edu), The Regents of the University of Michigan

 This library and application are part of the Uptane Project; 
 http://uptane.umtri.umich.edu/ ^ http://uptane.github.io/

 In accordance with the standard practices at the University of Michigan, this source code is released free of charge and without warranty as a contractual obligation to the funding party. All inquiries regarding usage should be directed to Sam Lauzon <slauzon at umich.edu>

 **NOT YET INTENDED FOR USE IN PRODUCTION ENVIRONMENTS AND MOSTLY INCOMPLETE**



LICENSE
---------------------------

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


DEPENDENCIES
--------------------------

  This demo application makes use of the following; 
  - cURL ( https://curl.haxx.se/ ) for Web hooks
  - JSON-C for Metadata Encoding
  - can-utils ( https://github.com/linux-can/can-utils ) for CAN Interaction

 There are no conflicts in the above license as of time of authorship and all software used in this demo application share the same license philosophies. (Generally, all contain copies of the MIT license.)

 There is an interface with companion instructions to allow anyone to wrap any external libraries being used to interact with servers, store/retrieve data and encode/decode metadata. This should also allow an implementation team to customize the HSM interactions to their specific interfaces, or interface with any existing OMA-DM libraries

 In addition, these libraries are interfaced through flexible wrapper code which may be easily modified to function with libraries of similar functionality.



USAGE
-----------------------------

 make from the top level should create two outputs, libuptane.so and uptaneclient.
   (On Win32, 3 outputs: libuptane.dll, libuptane.so and uptaneclient.exe - See NOTES)

NOTES
-------------------------
   This software is a work in progress. It is not intended (yet) to be deployed in production environments.

  Cygwin links against things called .dll. Compensations were made where possible to allow cygwin test environments.


  <ref 13/09/16/>

