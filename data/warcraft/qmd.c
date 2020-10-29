// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m血之盟约[2;37;0m[2;37;0m", ({"qmda"}));        
        set("gender", "男性");                
        set("long", "血之盟约[2;37;0m
它是星宿弟子的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "qmd");
        set("owner_name", "星宿弟子");
        set_temp("owner", "qmd");
        set_temp("owner_name", "星宿弟子");
        ::setup();
}
