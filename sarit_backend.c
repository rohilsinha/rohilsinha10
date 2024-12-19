#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to print HTTP header
void print_http_header() {
    printf("Content-Type: text/html\n\n");
}

// Function to handle GET requests
void handle_get_request(char *query_string) {
    print_http_header();
    printf("<html><head><title>Dynamic SARIT Backend</title></head><body>");
    if (query_string != NULL) {
        printf("<h1>Welcome to SARIT Backend!</h1>");
        printf("<p>Query: %s</p>", query_string);
    } else {
        printf("<h1>Welcome to SARIT Backend!</h1>");
        printf("<p>No Query Provided</p>");
    }
    printf("<a href='/'>Go Back</a></body></html>");
}

// Function to handle POST requests
void handle_post_request() {
    char *content_length_str = getenv("CONTENT_LENGTH");
    if (content_length_str != NULL) {
        int content_length = atoi(content_length_str);
        char *post_data = (char *)malloc(content_length + 1);
        if (post_data != NULL) {
            fread(post_data, 1, content_length, stdin);
            post_data[content_length] = '\0';

            print_http_header();
            printf("<html><head><title>SARIT Data Submission</title></head><body>");
            printf("<h1>Post Data Received</h1>");
            printf("<pre>%s</pre>", post_data);
            printf("<a href='/'>Go Back</a>");
            printf("</body></html>");

            free(post_data);
        }
    }
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");

    if (request_method == NULL) {
        print_http_header();
        printf("<html><body><h1>Error: REQUEST_METHOD not set</h1></body></html>");
        return 1;
    }

    if (strcmp(request_method, "GET") == 0) {
        char *query_string = getenv("QUERY_STRING");
        handle_get_request(query_string);
    } else if (strcmp(request_method, "POST") == 0) {
        handle_post_request();
    } else {
        print_http_header();
        printf("<html><body><h1>Error: Unsupported Request Method</h1></body></html>");
    }

    return 0;
}
