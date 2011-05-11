#include <stdio.h>

#include "v4l-test.h"
#include <stdio.h>
#include "network.h"

void send(struct buffer* b)
{
  printf("%s", b[0].start); /* data is in bs[0].start */
  // TODO: Send the image over the network.
  // TODO: Receive compressed video instead.
}
