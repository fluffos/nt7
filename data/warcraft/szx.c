// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m乌骓[2;37;0m[2;37;0m", ({"wuzhui"}));        
        set("gender", "女性");                
        set("long", "乌骓马出自于《西汉演义》中霸项羽的坐骑[2;37;0m
它是项羽的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "szx");
        set("owner_name", "项羽");
        set_temp("owner", "szx");
        set_temp("owner_name", "项羽");
        ::setup();
}
