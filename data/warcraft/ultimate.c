// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m命运狂想曲[2;37;0m[2;37;0m", ({"destiny"}));        
        set("gender", "男性");                
        set("long", "我命由我不由天，天欲灭我我灭天！[2;37;0m
它是太学主的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ultimate");
        set("owner_name", "太学主");
        set_temp("owner", "ultimate");
        set_temp("owner_name", "太学主");
        ::setup();
}
