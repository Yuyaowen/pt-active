#! /bin/sh

LOCKFILE=/tmp/track_generic_move_netcam.lock
[ -e "$LOCKFILE" ] && exit 0
> $LOCKFILE

echo "=== $TRACK_ACTION"

if [ "$TRACK_ACTION" = "move" ]; then
	if [ "$TRACK_CENT_X" -lt "$((TRACK_IMGS_WIDTH*3/8))" ]; then
		/home/yt/pt-active left low
	fi

	if [ "$TRACK_CENT_X" -gt "$((TRACK_IMGS_WIDTH*5/8))" ]; then
		/home/yt/pt-active right low
	fi

	if [ "$TRACK_CENT_Y" -lt "$((TRACK_IMGS_HEIGHT*3/8))" ]; then
		/home/yt/pt-active up low
	fi

	if [ "$TRACK_CENT_Y" -gt "$((TRACK_IMGS_HEIGHT*5/8))" ]; then
		/home/yt/pt-active down low
	fi
fi

sleep 0.8s
/home/yt/pt-active stop
rm -f "$LOCKFILE"
