// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("张扬[2;37;0m[2;37;0m", ({"zhangyang"}));        
        set("gender", "男性");                
        set("long", "扬哥出马 天下我有[2;37;0m
它是为红颜的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cqforred");
        set("owner_name", "为红颜");
        set_temp("owner", "cqforred");
        set_temp("owner_name", "为红颜");
        ::setup();
}
