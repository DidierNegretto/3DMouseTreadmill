<!-- Tufts VUE 3.3.0 concept-map (FSM.vue) 2020-01-01 -->
<!-- Tufts VUE: http://vue.tufts.edu/ -->
<!-- Do Not Remove: VUE mapping @version(1.1) jar:file:/Applications/VUE.app/Contents/Resources/Java/VUE.jar!/tufts/vue/resources/lw_mapping_1_1.xml -->
<!-- Do Not Remove: Saved date Wed Jan 01 09:44:46 CET 2020 by Didier on platform Mac OS X 10.14.5 in JVM 13.0.1+9 -->
<!-- Do Not Remove: Saving version @(#)VUE: built October 8 2015 at 1658 by tomadm on Linux 2.6.32-504.23.4.el6.x86_64 i386 JVM 1.7.0_21-b11(bits=32) -->
<?xml version="1.0" encoding="US-ASCII"?>
<LW-MAP xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:noNamespaceSchemaLocation="none" ID="0" label="FSM.vue"
    created="1577867148186" x="0.0" y="0.0" width="1.4E-45"
    height="1.4E-45" strokeWidth="0.0" autoSized="false">
    <resource referenceCreated="1577868286171"
        spec="/Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/report/fig/FSM.vue"
        type="1" xsi:type="URLResource">
        <title>FSM.vue</title>
        <property key="File" value="/Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/report/fig/FSM.vue"/>
    </resource>
    <fillColor>#FFFFFF</fillColor>
    <strokeColor>#404040</strokeColor>
    <textColor>#000000</textColor>
    <font>SansSerif-plain-14</font>
    <URIString>http://vue.tufts.edu/rdf/resource/604758ddc0a8010e642d3f6015e0ccbb</URIString>
    <child ID="6" label="STOP" layerID="1" created="1577867161525"
        x="635.0" y="232.5" width="112.0" height="54.0"
        strokeWidth="1.0" autoSized="false" xsi:type="node">
        <fillColor>#EA2218</fillColor>
        <strokeColor>#000000</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-plain-18</font>
        <URIString>http://vue.tufts.edu/rdf/resource/604758ddc0a8010e642d3f605713fc0a</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="7" label="SPEED" layerID="1" created="1577867213956"
        x="635.0" y="79.0" width="112.0" height="51.0" strokeWidth="1.0"
        autoSized="false" xsi:type="node">
        <fillColor>#F2AE45</fillColor>
        <strokeColor>#000000</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-plain-18</font>
        <URIString>http://vue.tufts.edu/rdf/resource/604758ddc0a8010e642d3f60e58911e6</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="8" label="LOAD" layerID="1" created="1577867237444"
        x="859.0" y="234.0" width="112.0" height="51.0"
        strokeWidth="1.0" autoSized="false" xsi:type="node">
        <fillColor>#F2AE45</fillColor>
        <strokeColor>#000000</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-plain-18</font>
        <URIString>http://vue.tufts.edu/rdf/resource/604758dec0a8010e642d3f608a0ef499</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="9" label="RUNNING" layerID="1" created="1577867252061"
        x="859.0" y="444.5" width="112.0" height="51.0"
        strokeWidth="1.0" autoSized="false" xsi:type="node">
        <fillColor>#F2AE45</fillColor>
        <strokeColor>#000000</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-plain-18</font>
        <URIString>http://vue.tufts.edu/rdf/resource/604758dec0a8010e642d3f60fd3551dc</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="10" label="If too many invalid measures ||&#xa;USER"
        layerID="1" created="1577867366165" x="568.0" y="128.5"
        width="246.0" height="105.5" strokeWidth="3.0" autoSized="false"
        controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#000000</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-italic-18</font>
        <URIString>http://vue.tufts.edu/rdf/resource/604758dec0a8010e642d3f6032233297</URIString>
        <point1 x="691.0" y="130.0"/>
        <point2 x="691.0" y="232.5"/>
        <ID1 xsi:type="node">7</ID1>
        <ID2 xsi:type="node">6</ID2>
    </child>
    <child ID="11" label="If too many invalid measures ||&#xa;USER"
        layerID="1" created="1577867485662" x="583.5371" y="285.0"
        width="276.9629" height="177.88464" strokeWidth="3.0"
        autoSized="false" controlCount="1" arrowState="2" xsi:type="link">
        <strokeColor>#000000</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-italic-18</font>
        <URIString>http://vue.tufts.edu/rdf/resource/604758dfc0a8010e642d3f60a9265b61</URIString>
        <point1 x="859.0" y="461.38464"/>
        <point2 x="683.1484" y="286.5"/>
        <ID1 xsi:type="node">9</ID1>
        <ID2 xsi:type="node">6</ID2>
        <ctrlPoint0 x="642.0" y="428.0" xsi:type="point"/>
    </child>
    <child ID="12" label="USER" layerID="1" created="1577867541709"
        x="745.5" y="95.83304" width="171.28735" height="139.66696"
        strokeWidth="3.0" autoSized="false" controlCount="1"
        arrowState="2" xsi:type="link">
        <strokeColor>#000000</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-italic-18</font>
        <URIString>http://vue.tufts.edu/rdf/resource/604758e0c0a8010e642d3f60412f7b0f</URIString>
        <point1 x="747.0" y="98.92478"/>
        <point2 x="915.28735" y="234.0"/>
        <ID1 xsi:type="node">7</ID1>
        <ID2 xsi:type="node">8</ID2>
        <ctrlPoint0 x="917.0" y="82.0" xsi:type="point"/>
    </child>
    <child ID="13" label="If i == MAX_POINTS" layerID="1"
        created="1577867886556" x="913.7483" y="283.5" width="169.0"
        height="162.5" strokeWidth="3.0" autoSized="false"
        controlCount="1" arrowState="2" xsi:type="link">
        <strokeColor>#000000</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-italic-18</font>
        <URIString>http://vue.tufts.edu/rdf/resource/604758e0c0a8010e642d3f60af6a8046</URIString>
        <point1 x="948.5" y="444.5"/>
        <point2 x="946.4931" y="285.0"/>
        <ID1 xsi:type="node">9</ID1>
        <ID2 xsi:type="node">8</ID2>
        <ctrlPoint0 x="1049.0" y="368.0" xsi:type="point"/>
    </child>
    <child ID="14" label="&#x9;USER" layerID="1" created="1577867889237"
        x="820.6067" y="283.5" width="72.46088" height="162.5"
        strokeWidth="3.0" autoSized="false" controlCount="1"
        arrowState="2" xsi:type="link">
        <strokeColor>#000000</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-italic-18</font>
        <URIString>http://vue.tufts.edu/rdf/resource/604758e0c0a8010e642d3f6003b8ab99</URIString>
        <point1 x="888.85925" y="285.0"/>
        <point2 x="891.56757" y="444.5"/>
        <ID1 xsi:type="node">8</ID1>
        <ID2 xsi:type="node">9</ID2>
        <ctrlPoint0 x="813.0" y="359.0" xsi:type="point"/>
    </child>
    <child ID="15" label="i = (duration(i)) == 0 ? 0 : i++" layerID="1"
        created="1577868163297" x="810.9733" y="473.5" width="233.0"
        height="60.345215" strokeWidth="3.0" autoSized="false"
        controlCount="2" arrowState="2" xsi:type="link">
        <strokeColor>#000000</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-italic-18</font>
        <URIString>http://vue.tufts.edu/rdf/resource/604758e1c0a8010e642d3f60bc122eca</URIString>
        <point1 x="867.05145" y="495.10657"/>
        <point2 x="974.0" y="475.0"/>
        <ID1 xsi:type="node">9</ID1>
        <ctrlPoint0 x="777.57794" y="541.95636" xsi:type="point"/>
        <ctrlPoint1 x="1082.0004" y="528.9286" xsi:type="point"/>
    </child>
    <layer ID="1" label="Layer 1" created="1577867148193" x="0.0"
        y="0.0" width="1.4E-45" height="1.4E-45" strokeWidth="0.0" autoSized="false">
        <URIString>http://vue.tufts.edu/rdf/resource/604758e1c0a8010e642d3f60143213cf</URIString>
    </layer>
    <userZoom>1.0</userZoom>
    <userOrigin x="-14.0" y="-14.0"/>
    <presentationBackground>#202020</presentationBackground>
    <PathwayList currentPathway="0" revealerIndex="-1">
        <pathway ID="0" label="Percorso senza titolo"
            created="1577867148185" x="0.0" y="0.0" width="1.4E-45"
            height="1.4E-45" strokeWidth="0.0" autoSized="false"
            currentIndex="-1" open="true">
            <strokeColor>#B3CC33CC</strokeColor>
            <textColor>#000000</textColor>
            <font>SansSerif-plain-14</font>
            <URIString>http://vue.tufts.edu/rdf/resource/604758e1c0a8010e642d3f60b0ee6362</URIString>
            <masterSlide ID="2" created="1577867148203" x="0.0" y="0.0"
                width="800.0" height="600.0" locked="true"
                strokeWidth="0.0" autoSized="false">
                <fillColor>#000000</fillColor>
                <strokeColor>#404040</strokeColor>
                <textColor>#000000</textColor>
                <font>SansSerif-plain-14</font>
                <URIString>http://vue.tufts.edu/rdf/resource/604758e2c0a8010e642d3f608e682256</URIString>
                <titleStyle ID="3" label="Header"
                    created="1577867148211" x="340.5" y="175.0"
                    width="119.0" height="50.0" strokeWidth="0.0"
                    autoSized="true" isStyle="true" xsi:type="node">
                    <strokeColor>#404040</strokeColor>
                    <textColor>#FFFFFF</textColor>
                    <font>Gill Sans-plain-36</font>
                    <URIString>http://vue.tufts.edu/rdf/resource/604758e2c0a8010e642d3f603a6a1ad0</URIString>
                    <shape xsi:type="rectangle"/>
                </titleStyle>
                <textStyle ID="4" label="Slide Text"
                    created="1577867148212" x="349.0" y="282.5"
                    width="102.0" height="35.0" strokeWidth="0.0"
                    autoSized="true" isStyle="true" xsi:type="node">
                    <strokeColor>#404040</strokeColor>
                    <textColor>#FFFFFF</textColor>
                    <font>Gill Sans-plain-22</font>
                    <URIString>http://vue.tufts.edu/rdf/resource/604758e6c0a8010e642d3f6091df2eba</URIString>
                    <shape xsi:type="rectangle"/>
                </textStyle>
                <linkStyle ID="5" label="Links" created="1577867148212"
                    x="375.0" y="385.0" width="50.0" height="30.0"
                    strokeWidth="0.0" autoSized="true" isStyle="true" xsi:type="node">
                    <strokeColor>#404040</strokeColor>
                    <textColor>#B3BFE3</textColor>
                    <font>Gill Sans-plain-18</font>
                    <URIString>http://vue.tufts.edu/rdf/resource/604758e7c0a8010e642d3f60962c9407</URIString>
                    <shape xsi:type="rectangle"/>
                </linkStyle>
            </masterSlide>
        </pathway>
    </PathwayList>
    <date>2020-01-01</date>
    <modelVersion>6</modelVersion>
    <saveLocation>/Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/report/fig</saveLocation>
    <saveFile>/Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/report/fig/FSM.vue</saveFile>
</LW-MAP>
