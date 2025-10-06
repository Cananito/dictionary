#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <stdio.h>

int main() {
  // TODO: Get input from args.
  char* input = "programming";

  CFStringRef input_string = CFStringCreateWithCString(NULL,
                                                       input,
                                                       kCFStringEncodingUTF8);
  CFRange input_range = CFRangeMake(0, CFStringGetLength(input_string));

  CFStringRef result_string = DCSCopyTextDefinition(NULL,
                                                    input_string,
                                                    input_range);

  CFRelease(input_string);

  // TODO: Do a more precise allocation size.
  CFIndex buffer_size = CFStringGetLength(result_string) * 2;
  char* result = calloc(buffer_size, sizeof(char));
  CFStringGetCString(result_string, result, buffer_size, kCFStringEncodingUTF8);

  CFRelease(result_string);

  printf("%s\n", result);

  free(result);

  return 0;
}
