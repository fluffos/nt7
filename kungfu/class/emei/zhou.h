//Cracked by Roath
// /kungfu/class/emei/zhou.h
// yasuko: 2000/08/17
// mantian: may/21/2001
// kick out ppl for those learn pxj after bai zhou
// xiaojian for fixing all of the bugs June 22,2001
// xQin 06/01 add a log for expelled students 
#include <ansi.h>

void init()
{
        object ob,me;
        ob=this_player();
        me=this_object();

        ::init();

        set_heart_beat(1);

        if(interactive(ob)
                 && query("family/family_name", ob) == "峨嵋派"
                 && query("gender", ob) == "无性"
                && (int)ob->query_skill("pixie-jian", 1) >=1) {
                if( !query("pxj_warning", ob)){
                        set("pxj_warning", 1, ob);
                        command("hmm");
                        command("say 正邪不两立,你为何去偷学辟邪剑法? 赶快改过自新,否则下次见到你定不轻饶!\n");
                } else {
                command("look "+getuid(ob));
                command("hmm "+getuid(ob));
                command("sneer "+getuid(ob));
                command("say "+RANK_D->query_rude(ob)+"即然学了九阴真经上的功夫，为何去学辟邪剑法，嫌我教的不够好？");
                command("expell"+query("id", ob));
                command("say 滚吧！");
                delete("pxj_warning", ob);
                write_file("/kungfu/class/emei/zhou_log.c",
                sprintf("%s(%s)wasexpelledbyzhouduetopxj%d(%d).\n",query("id", this_player()),ctime(time())));
                }
        }
}
string ask_jiuyin()
{
        object ob,me=this_player();
        if( query("family/master_name", me) != "周芷若" )
                return RANK_D->query_respect(this_player())+"与我素不相识，何出此言呢？";
        ob=new(__DIR__"obj/jiuyin-paper");
        if (present("juan pian",me)) return "咦，你身上不是带着九阴真经了吗，怎么还来问我？";
        if (!ob) return "嗯，借给你倒是没问题，只是刚被别的弟子借走了，你过一阵再来问问吧。";
        if( !query("jiuyin/first", me)){
                command ("say 你是第一次来借九阴真经吧？\n
            这束绢片是密抄本的九阴真经，原来藏在倚天剑里，其实也不是什么大不了的东西，
            你拿去翻翻吧。\n
            为师以前年轻不懂事，只知道照着书上的招式修炼(xiulian)，虽然进展很快，但
            是越练到后来，越是凶险。如果不能潜心领悟(lingwu)九阴真经中的真谛，终究无
            法有所大成。当然，领悟的话会慢很多。你要是有什么不明白的，就直接过来跟我
            学吧。\n");
                set("jiuyin/first", 1, me);
        }
        ob->move(me);
        message_vision("$n递给$N一束绢片。\n",me,this_object());
        command("rumor"+query("name", me)+"弄到了九阴真经密抄本。");
        return "记住师父的话，千万不要贪功急进，否则到时候就后悔莫及了。";
}

void attempt_apprentice(object ob)
{
    mapping fam;
    int last_betray,shen;
        
        //xiaojian: added a check before recruiting, i.e. won't recruit pxj dizi.

                if ((int)ob->query_skill("pixie-jian", 1) >=1) {
                        command("ah"+query("id", ob));
                        command("say 小女子与朝廷素无往来，不知这位大人到此有何公干？");
                        return;
                 }

        // Yinli and Qianzhu-wandu: by yasuko
        if ((int)ob->query_skill("qianzhu-wandu", 1) >=1 ) {
                command("sneer"+query("id", ob));
                command("say 这位" + RANK_D->query_respect(this_player())
                + "与殷姑娘渊源非浅，在下可不敢误人子弟。");
                return;
        }
        // Emei dizi(Linji-zhuang & Pixie-jian)：by yasuko
        if( query("family/family_name", ob) == "峨嵋派"){
                if ((int)ob->query_skill("linji-zhuang", 1) < 90) {
                        command ("say " + RANK_D->query_respect(this_player()) +
                                 "的临济庄尚欠火侯， 不宜学习上乘武功。\n");
                        return;
                }
                if ((int)ob->query_skill("pixie-jian", 1) >=1) {
                        command("sigh4 " );
                        command("say 这位" + RANK_D->query_respect(this_player())
                                + "既然不稀罕本门的武功，又何必来找我呢？");
                        return;
                }
        }
        // Betryer
        else {
                // Ppl who has betraied zhou and left from emei
                last_betray=query("zhou-betray", ob);
                if( last_betray>0 && last_betray != query("betrayer", ob )
                 && query("combat_exp", ob) >= 10000){
                        command ("say " + RANK_D->query_respect(this_player()) +
                        "既然叛出峨嵋, 此刻想回却已晚了. \n");
                        command ("say " + RANK_D->query_respect(this_player()) + "是"
                        +query("family/family_name", ob)+"高手，本派可不敢收留！");
                        return;
                }
                // Gaibang Hinghand
                if( query("family/family_name", ob) == "丐帮" && query("rank", ob)>1){
                        command("say " + RANK_D->query_respect(ob) + "是丐帮高手，恕我不能收你。");
                        return;
                }
                // Pixie-jian: by yasuko
                if ((int)ob->query_skill("pixie-jian", 1) >=1) {
                        command("ah"+query("id", ob));
                        command("say 小女子与朝廷素无往来，不知这位大人到此有何公干？");
                        return;
                 }
                // Peaceful life 1: by yasuko
                shen=query("shen", ob);
                if (shen >0) {
                        if (random(shen) >= 1000 ) {
                                command("xixi"+query("id", ob));
                                command("say " + RANK_D->query_respect(this_player()) + 
                                "侠名远播，这师徒之称实在是折杀小女子了。");
                                return;
                        }
                }
                if (shen <0) {
                        shen = 0 - shen;
                        if (random(shen) >= 1000 ) {
                                command("hmm" );
                                command("say 素闻" + RANK_D->query_respect(this_player()) + 
                                "是黑道里响当当的人物，你若是真能洗心革面，那我就收下你。");
                                return;
                        }
                }
                // Peaceful life 2: by yasuko
                if( random(query("PKS", ob)/query("death_times", ob))>10){
                        command("lazy");
                        command("say 这位" + RANK_D->query_respect(this_player()) + 
                        "怎么满脸的杀气？小女子怕得很，请改日再来吧。");
                        return;
                }
        }
        // Giving everybody one chance to enter emei
        if ((int)ob->query_skill("claw", 1) < 40) {
                command("say 我看你是来学九阴真经上的功夫吧，先去学点儿基本爪法再来吧。");
                return;
        }
        if ((int)ob->query_skill("jiuyin-baiguzhao", 1) < 40) {
                command("say 我看你是来学九阴真经上的功夫吧，先去学点儿基本的九阴爪再来吧。");
                return;
        }
        command("say 好吧，你就跟我这儿学吧。"); 
        command("say 不过你可记住了, 要是你今后背叛师门, 我可不会再收你.\n");
        command("recruit "+query("id", ob));
        set("emei", 1, ob);
        set("zhou-betray",query("betrayer",  ob), ob);
        command("whisper"+query("id", ob)+
                        " 下次来找我时，到九老洞口叫一声，“有侣乎？”我就会找人带你进来.\n");
}
