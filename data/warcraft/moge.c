// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m小咪[2;37;0m[2;37;0m", ({"xiaomi"}));        
        set("gender", "女性");                
        set("long", "摸哥的小咪咪[2;37;0m
它是十八摸的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "moge");
        set("owner_name", "十八摸");
        set_temp("owner", "moge");
        set_temp("owner_name", "十八摸");
        ::setup();
}
