#include <gst/gst.h>

int main(int argc, char **argv){
	GstElement *pipeline;
	GstBus *bus;
	GstMessage *msg;

	gst_init(&argc, &argv);

	pipeline = gst_parse_launch("playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm", NULL);
	return 0;
}
