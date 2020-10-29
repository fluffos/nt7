// banghui.h
// 帮会定义文件

// 房间长描述限定
protected nosave int room_desc_l = 52, room_desc_h = 6;

// 房间最大出口数
protected nosave int max_exits = 5;

// 每个房间最多定义的 action 数目
protected nosave int max_action_per_room = 2;

protected nosave mapping r_dir = ([
        "north"         : "south",
        "south"         : "north",
        "west"          : "east",
        "east"          : "west",
        "northwest"     : "southeast",
        "northeast"     : "southweat",
        "southwest"     : "northeast",
        "southeast"     : "northwest",
        "northup"       : "southdown",
        "northdown"     : "southup",
        "southup"       : "northdown",
        "southdown"     : "northup",
        "westup"        : "eastdown",
        "westdown"      : "eastup",
        "eastup"        : "westdown",
        "eastdown"      : "westup",
        "enter"         : "out",
        "out"           : "enter",
]);

protected nosave string vdirs = "north south west east
northwest northeast southwest southeast
northup northdown southup southdown
westup westdown eastup eastdown
enter out";


