// story:nanhai 南海传说

#include <ansi.h>

int give_gift(string name);

nosave mixed *story = ({
        "哗～～～哗～～～轰隆！",
        "渔民：不好啦～～海啸啦～～～快逃啊～～～",
        "哗～～～哗～～～轰隆！",
        "眼见海水不住的蔓延，昔日浅滩，尽成汪洋。",
        "恩？",
        "南海神尼蓦然睁开双眼，暗道：何方妖物？",
        "哗～～哗～～",
        "神尼喝道：“原来是你这个孽障！又在兴风作浪，休要猖狂，吃我一掌！”",
        "啪！",
        "南海恶蛟：嘿嘿嘿嘿，什么人这么不识好歹？",
        "神尼直震得眼花缭乱，气血翻涌，暗道：枉空我修炼百年，居然如此不济。",
        "不及多想，神尼赶紧卷铺盖，自念道：赶紧上华山找独孤求败那老头，难怪他躲在山上，有道理！",
        (: give_gift, "nanhai" :),
        "听说南海恶蛟(monster dragon)重出大海，到人间兴风作浪。",
});

string prompt() { return HIM "【神话】" NOR; }

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

int give_gift(string name)
{
        object ob;

        ob = new(CLASS_D("misc/") + name);
        if (! objectp(ob))
                return 0;

        NPC_D->place_npc(ob);
        if (! objectp(environment(ob)))
        {
                destruct(ob);
                return 0;
        }

        CHANNEL_D->do_channel(find_object(STORY_D), "sys",
                              ob->name() + "出现在" + environment(ob)->short() +
                              "(" + base_name(environment(ob)) + ")。");
        return 1;
}
