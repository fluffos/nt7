// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m氤氲[2;37;0m[2;37;0m", ({"yinyun"}));        
        set("gender", "男性");                
        set("long", "尔其动也，风雨如晦，雷电共作；尔其静也，体象皎镜，星开碧落。[2;37;0m
它是碧落的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "biluo");
        set("owner_name", "碧落");
        set_temp("owner", "biluo");
        set_temp("owner_name", "碧落");
        ::setup();
}
