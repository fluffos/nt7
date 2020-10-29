inherit VRM_SERVER;

void create()
{
        set_inherit_room( __DIR__"lin" );

        set_maze_long(8);

        //入口方向(出口在对面)
        set_entry_dir("south");

        //入口与区域的连接方向
        set_link_entry_dir("south");

        set_link_entry_room(__DIR__"gd1");

        set_link_exit_dir("north");

        set_link_exit_room(__DIR__"dmq");

        set_entry_short("浓密树林");

        //入口房间描述
        set_entry_desc(@LONG
这里是一片浓密的树林，参天的大树遮天蔽日，偶尔有几缕
光线透进来。地上满是枯枝败叶，空气中弥漫着让人不安的气氛。
LONG
);

        //出口房间短描述
        set_exit_short("浓密树林");

        //出口房间描述
        set_exit_desc(@LONG
这里是一片浓密的树林，参天的大树遮天蔽日，偶尔有几缕
光线透进来。地上满是枯枝败叶，空气中弥漫着让人不安的气氛。
LONG
);

        set_outdoors(1);

        set_valid_rooms( ({
        __DIR__"lin",
}));

        create_maze();
}

string query_my_map()
{
        return read_file(__DIR__"shulin.map");
}

