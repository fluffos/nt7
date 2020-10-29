// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老马[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "老马[2;37;0m
它是情与老歌的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qianmk");
        set("owner_name", "情与老歌");
        set_temp("owner", "qianmk");
        set_temp("owner_name", "情与老歌");
        ::setup();
}
