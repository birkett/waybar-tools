# DBus Interface

The files in this directory have been generated using libdbus-c++ tools.

SpotifyDBus.xml:
```shell
dbusxx-introspect /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.spotify
```

Headers:
```shell
dbusxx-xml2cpp SpotifyDBus.xml --proxy=SpotifyProxy.h --adaptor=SpotifyAdaptor.h
```
