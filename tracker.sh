#! /bin/sh

LOCKFILE=/tmp/track_generic_move_netcam.lock
[ -e "$LOCKFILE" ] && exit 0
> $LOCKFILE

if [ "$TRACK_ACTION"x == "move"x ]; then
	if [ "$TRACK_CENT_X" -lt "$((TRACK_IMGS_WIDTH*3/8))" ]; then
		pt-active left
	fi

	if [ "$TRACK_CENT_X" -gt "$((TRACK_IMGS_WIDTH*5/8))" ]; then
		pt-active right
	fi

	if [ "$TRACK_CENT_Y" -lt "$((TRACK_IMGS_HEIGHT*3/8))" ]; then
		pt-active up
	fi

	if [ "$TRACK_CENT_Y" -gt "$((TRACK_IMGS_HEIGHT*5/8))" ]; then
		pt-active down
	fi
fi

sleep 1
pt-active stop
rm -f "$LOCKFILE"
