// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m巧[2;37;0m[2;37;0m", ({"qiao"}));        
        set("gender", "男性");                
        set("long", "花和巧[2;37;0m
它是吖小的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "grass");
        set("owner_name", "吖小");
        set_temp("owner", "grass");
        set_temp("owner_name", "吖小");
        ::setup();
}
