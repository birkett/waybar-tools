# Spotify DBus Interface

The files in this directory have been generated using libdbus-c++ tools.

These have been used to create a minimal implementation, SpotifyDBusInterface.

SpotifyDBus.xml:
```shell
dbusxx-introspect /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.spotify
```

Headers:
```shell
dbusxx-xml2cpp SpotifyDBus.xml --proxy=SpotifyProxy.h --adaptor=SpotifyAdaptor.h
```

The player can be manually queried:
```shell
dbus-send \
  --print-reply \
  --dest=org.mpris.MediaPlayer2.spotify \
  /org/mpris/MediaPlayer2 \
  org.freedesktop.DBus.Properties.Get \
  string:'org.mpris.MediaPlayer2.Player' \
  string:'PlaybackStatus'
```
