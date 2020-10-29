// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m麒麟[2;37;0m[2;37;0m", ({"dsy"}));        
        set("gender", "女性");                
        set("long", "这是一只麒麟[2;37;0m
它是快乐小董的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dongyaowei");
        set("owner_name", "快乐小董");
        set_temp("owner", "dongyaowei");
        set_temp("owner_name", "快乐小董");
        ::setup();
}
