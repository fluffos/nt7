// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小公鸡[2;37;0m[2;37;0m", ({"gongji"}));        
        set("gender", "男性");                
        set("long", "不解释。[2;37;0m
它是小飞的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xfei");
        set("owner_name", "小飞");
        set_temp("owner", "xfei");
        set_temp("owner_name", "小飞");
        ::setup();
}
