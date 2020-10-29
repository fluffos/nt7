// story:zhuque 朱雀

#include <ansi.h>

int give_gift(string name);

nosave mixed *story = ({
        "火焰山，唐僧师徒 ……",
        "唐僧一脸愁容：这火焰山的火不熄灭，如何过得去啊！",
        "沙僧：不要着急师父，猴哥已经去牛魔王那里借芭蕉扇了。",
        "猪八戒：算了吧，师傅，咱们就此散了吧，我回我的高老庄，沙师弟回他的流沙河，\n"
        "            猴哥就回花果山当他的美猴王 ……， 师父，沙师弟，你们说如何？",
        "唐僧开始认真考虑这个问题！",
        "沙僧开始认真考虑这个问题！",
        "…… …… ……",
        "孙悟空：师父——，我回来了，我从牛哥那里借来了芭蕉扇！",
        "唐僧：阿们，总算借到了，悟空，开工~~！",
        "孙悟空双手挥舞着芭蕉扇，刹那间狂风骤起，暴雨倾泻而下 ……",
        "唐僧大声嚷嚷道：“小心啦，打雷啦！下雨收衣服啦！”",
        "…… …… ……",
        "火焰山的火渐渐熄灭！",
        "…… …… ……",
        "刹那间，风止雨停，地动山摇，火焰山中传出阵阵巨响。", 
        "突然，一只巨大的浑身火红的凤凰伴随着惊天动地般的叫声冲出火焰山……",
        "孙悟空：妖怪？！",
        "猪八戒：⊙⊙ ！？",
        "沙僧：神兽？！",
        "唐僧：跑啊~~~~~~~ ！",
        "…… …… ……",
        "唐僧师徒四人瞬间消失得无影无踪。",        
        "......",
        (: give_gift, "zhuque" :),
        "听说朱雀(fire phoenix)从睡梦中惊醒，逃出了火焰山。",       
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
