#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <getopt.h>
#include <stdio.h>

static void print_definition(char const* const input_word) {
  CFStringRef input_string = CFStringCreateWithCString(NULL,
                                                       input_word,
                                                       kCFStringEncodingUTF8);
  CFRange input_range = CFRangeMake(0, CFStringGetLength(input_string));
  CFStringRef result_string = DCSCopyTextDefinition(NULL,
                                                    input_string,
                                                    input_range);
  CFRelease(input_string);
  if (!result_string) {
    printf("<no definition found>\n");
    return;
  }
  // TODO: Do a more precise allocation size.
  CFIndex buffer_size = CFStringGetLength(result_string) * 2;
  char* result = calloc(buffer_size, sizeof(char));
  CFStringGetCString(result_string, result, buffer_size, kCFStringEncodingUTF8);
  CFRelease(result_string);
  printf("%s\n", result);
  free(result);
}

static void print_usage(void) {
  printf("Usage:\n");
  printf("  dictionary [word]\n");
}

static char* short_opts = "vh";
static struct option long_opts[] = {
  { .name = "version", .has_arg = no_argument, .flag = 0, .val = 'v' },
  { .name = "help", .has_arg = no_argument, .flag = 0, .val = 'h' },
  { 0, 0, 0, 0 },
};

int main(int argc, char** argv) {
  int val;
  while ((val = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1) {
    switch (val) {
      case 'v': {
        printf("Version 1.0\n");
        return 0;
      }
      case 'h': {
        print_usage();
        return 0;
      }
      default: {
        print_usage();
        return 0;
      }
    }
  }
  if (argc > 2) {
    printf("[Only defining the first word, ignoring the rest.]\n");
  }
  print_definition(argv[1]);
  return 0;
}
