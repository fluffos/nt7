// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("奇幻旅行[2;37;0m[2;37;0m", ({"mahua"}));        
        set("gender", "女性");                
        set("long", "我的我的是我的[2;37;0m
它是笨鸟先飞的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "gaokeyu");
        set("owner_name", "笨鸟先飞");
        set_temp("owner", "gaokeyu");
        set_temp("owner_name", "笨鸟先飞");
        ::setup();
}
