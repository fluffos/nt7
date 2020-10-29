// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("落雁[2;37;0m[2;37;0m", ({"luoyan"}));        
        set("gender", "女性");                
        set("long", "落雁[2;37;0m
它是慕容紫颜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ziyan");
        set("owner_name", "慕容紫颜");
        set_temp("owner", "ziyan");
        set_temp("owner_name", "慕容紫颜");
        ::setup();
}
