#include <ansi.h>
int give_gift();
mixed *story = 
({
        "【泥潭福利公告】王者归来福利彩票正式发行！",
        "【泥潭福利公告】由冼老板全权代理彩票发行及兑奖。",
        "…………",
        "冼老板：为纪念雄霸天下……现在正式发行彩票……",
        "嘈杂声：“快挤啊，听说前几号的中奖机会大啊”……",
        "“大家排队，这不是93年发行股票认购证，这是福利彩票啊，你看你，",
        "话没说完就把那个小孩推到了，你这是什么爱心啊？那边那个，你！啊",
        "要懂得礼让嘛！唉……”",
        "一张彩票从冼老板的手指缝里掉了出来。谁都没有注意。",
        "……好不容易完成了一天的工作……",
        "“恩？怎么少了一张？好象被挤掉了！Faint！”",
        (: give_gift :),
});

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

int give_gift()
{
        STORY_D->give_gift("/task/story/lottery", 1,
                           HIM "\n一张 彩票 飘到你的面前。\n\n" NOR);
        return 0;
}
