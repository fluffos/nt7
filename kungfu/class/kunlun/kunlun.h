// kunlun.h

int permit_recruit(object ob)
{
        return notify_fail("暂不开放\n");
        
        if( query("detach/昆仑派", ob) || 
            query("betrayer/昆仑派", ob) )
        {
                command("say 亏你还有脸回我昆仑山？给我滚开！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 阁下不忠不信，我最痛恨你这种人了。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "昆仑派" )
        {
                command("say 阁下既有了名师指点，还来我们昆仑派做什么？");
                return 0;
        }

        return 1;
}
