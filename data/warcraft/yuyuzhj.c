// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("路虎[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "路虎[2;37;0m
它是小祖宗的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "yuyuzhj");
        set("owner_name", "小祖宗");
        set_temp("owner", "yuyuzhj");
        set_temp("owner_name", "小祖宗");
        ::setup();
}
