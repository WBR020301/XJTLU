package com.bosch.adcc;
import java.util.List;
import java.util.ArrayList;
import java.nio.ByteBuffer;
import com.gitee.openasam.autosar.type.*;
import com.google.gson.annotations.SerializedName;

/**
 * <pre>
 * &lt;STD-CPP-IMPLEMENTATION-DATA-TYPE UUID="5636e855-58fe-4bc7-af89-f79a2c2a5bf6"&gt;
              &lt;SHORT-NAME&gt;IDT_ADAS_arr_DynamicObjects&lt;/SHORT-NAME&gt;
              &lt;CATEGORY&gt;VECTOR&lt;/CATEGORY&gt;
              &lt;TEMPLATE-ARGUMENTS&gt;
                &lt;CPP-TEMPLATE-ARGUMENT&gt;
                  &lt;TEMPLATE-TYPE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_ADAS_strt_DynamicObject&lt;/TEMPLATE-TYPE-REF&gt;
                &lt;/CPP-TEMPLATE-ARGUMENT&gt;
              &lt;/TEMPLATE-ARGUMENTS&gt;
              &lt;TYPE-EMITTER&gt;TYPE_EMITTER_ARA&lt;/TYPE-EMITTER&gt;
            &lt;/STD-CPP-IMPLEMENTATION-DATA-TYPE&gt;

 * </pre>
 Date: Nov 28, 2024
 Author: anping.mao@cn.bosch.com
 */
public class IDTADASArrDynamicObjects extends Object implements SomeipTransformer{
    //OBJ

    /*
     * /DataType/StdCppImplDataType/IDT_ADAS_strt_DynamicObject
     */
     @SerializedName("vector")
    private List<IDTADASStrtDynamicObject> vector;

    /**
     * generated from:
     * &lt;STD-CPP-IMPLEMENTATION-DATA-TYPE UUID="5636e855-58fe-4bc7-af89-f79a2c2a5bf6"&gt;
              &lt;SHORT-NAME&gt;IDT_ADAS_arr_DynamicObjects&lt;/SHORT-NAME&gt;
              &lt;CATEGORY&gt;VECTOR&lt;/CATEGORY&gt;
              &lt;TEMPLATE-ARGUMENTS&gt;
                &lt;CPP-TEMPLATE-ARGUMENT&gt;
                  &lt;TEMPLATE-TYPE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_ADAS_strt_DynamicObject&lt;/TEMPLATE-TYPE-REF&gt;
                &lt;/CPP-TEMPLATE-ARGUMENT&gt;
              &lt;/TEMPLATE-ARGUMENTS&gt;
              &lt;TYPE-EMITTER&gt;TYPE_EMITTER_ARA&lt;/TYPE-EMITTER&gt;
            &lt;/STD-CPP-IMPLEMENTATION-DATA-TYPE&gt;

     */
    public List<IDTADASStrtDynamicObject> getVector(){
        return this.vector;
    }

    public void setVector(List<IDTADASStrtDynamicObject> value){
        this.vector=value;
    }

    /**
     * read to this object from a buffer context
     */
    public void contextRead(final ByteBuffer buffer) {
                // list
                vector=new ArrayList<>();
                // it is dynamic VECTOR type
                int size = buffer.getInt();//remainings bytes not object counts!!!
                if(size>0) {
                    int startPos =buffer.position();
                    IDTADASStrtDynamicObject item = new IDTADASStrtDynamicObject();
                    item.contextRead(buffer);
                    this.vector.add(item);
                    int endPos = buffer.position();
                    int sizeof = endPos - startPos;

                    int resetObjectCount = size/sizeof - 1;
                    for(int i=0;i<resetObjectCount;i++){
                        item = new IDTADASStrtDynamicObject();
                        item.contextRead(buffer);
                        this.vector.add(item);
                    }
                }
    }
}