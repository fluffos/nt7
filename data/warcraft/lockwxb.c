// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m西[1;31m方[1;32m极[1;35m乐[2;37;0m[2;37;0m", ({"liudao"}));        
        set("gender", "男性");                
        set("long", "如梦似幻的西方极乐净土，不沾一丝人间烟尘。[2;37;0m
它是神话的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lockwxb");
        set("owner_name", "神话");
        set_temp("owner", "lockwxb");
        set_temp("owner_name", "神话");
        ::setup();
}
