package com.bosch.adcc;
import java.util.List;
import java.util.ArrayList;
import java.nio.ByteBuffer;
import com.gitee.openasam.autosar.type.*;
import com.google.gson.annotations.SerializedName;

/**
 * <pre>
 * &lt;STD-CPP-IMPLEMENTATION-DATA-TYPE UUID="67cb1acf-1300-427a-96e8-586ebe64a59f"&gt;
              &lt;SHORT-NAME&gt;IDT_ADAS_strt_DynamicObject&lt;/SHORT-NAME&gt;
              &lt;CATEGORY&gt;STRUCTURE&lt;/CATEGORY&gt;
              &lt;SUB-ELEMENTS&gt;
                &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="f8180a3e-ee97-450c-84a2-21a13fe3d13d"&gt;
                  &lt;SHORT-NAME&gt;DTE_objectId&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_Gen_val_ID&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;
                &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="68bc9e88-3b74-4f61-938e-9221c251ad4a"&gt;
                  &lt;SHORT-NAME&gt;DTE_objectType&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_ADAS_enum_DynamicObjectType&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;
                &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="6be5a3df-ecb9-4a5f-ad98-8d7267229e3e"&gt;
                  &lt;SHORT-NAME&gt;DTE_lightStatus&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_ADAS_enum_LightStatus&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;
                &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="8c1870bb-7c4c-4f82-8e2e-aded02da949c"&gt;
                  &lt;SHORT-NAME&gt;DTE_objectPoseX&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_Gen_val_Coordinate_X&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;
                &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="ee3e7b5d-6bc6-425f-9cfc-e713489b72e3"&gt;
                  &lt;SHORT-NAME&gt;DTE_objectPoseY&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_Gen_val_Coordinate_Y&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;
                &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="1254e902-77da-435d-871b-bf2a52a74f80"&gt;
                  &lt;SHORT-NAME&gt;DTE_objectYaw&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_Gen_val_Yaw&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;
                &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="90b31beb-6480-48e4-b882-752ce3a77782"&gt;
                  &lt;SHORT-NAME&gt;DTE_objectColor&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_ADAS_enum_ObjectColor&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;
                &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="f3df3912-3a02-42a5-8d0d-4ab5b8cb0954"&gt;
                  &lt;SHORT-NAME&gt;DTE_objectVelocityX&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_ADAS_val_vehicleSpd&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;
                &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="3322d84b-e6cb-48d1-8e9c-80409943b5ce"&gt;
                  &lt;SHORT-NAME&gt;DTE_objectVelocityY&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_ADAS_val_vehicleSpd&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;
                &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="1f327bdd-32dc-48f8-b075-0c031e74ea6a"&gt;
                  &lt;SHORT-NAME&gt;DTE_timestampnSec&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_ADAS_val_timestampnSec&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;
                &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="f30e026c-59c2-4018-946e-d66ca424af7f"&gt;
                  &lt;SHORT-NAME&gt;DTE_laneID&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_ADAS_val_laneID&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;
              &lt;/SUB-ELEMENTS&gt;
              &lt;TYPE-EMITTER&gt;TYPE_EMITTER_ARA&lt;/TYPE-EMITTER&gt;
            &lt;/STD-CPP-IMPLEMENTATION-DATA-TYPE&gt;

 * </pre>
 Date: Nov 28, 2024
 Author: anping.mao@cn.bosch.com
 */
public class IDTADASStrtDynamicObject extends Object implements SomeipTransformer{
    //OBJ

    /*
     * /DataType/StdCppImplDataType/IDT_Gen_val_ID  DTE_objectId
     */
     @SerializedName("id")
    private IDTGenValID id;
    /*
     * /DataType/StdCppImplDataType/IDT_ADAS_enum_DynamicObjectType  DTE_objectType
     */
     @SerializedName("type")
    private IDTADASEnumDynamicObjectType type;
    /*
     * /DataType/StdCppImplDataType/IDT_ADAS_enum_LightStatus  DTE_lightStatus
     */
     @SerializedName("light")
    private IDTADASEnumLightStatus light;
    /*
     * /DataType/StdCppImplDataType/IDT_Gen_val_Coordinate_X  DTE_objectPoseX
     */
     @SerializedName("x")
    private IDTGenValCoordinateX x;
    /*
     * /DataType/StdCppImplDataType/IDT_Gen_val_Coordinate_Y  DTE_objectPoseY
     */
     @SerializedName("y")
    private IDTGenValCoordinateY y;
    /*
     * /DataType/StdCppImplDataType/IDT_Gen_val_Yaw  DTE_objectYaw
     */
     @SerializedName("yaw")
    private IDTGenValYaw yaw;
    /*
     * /DataType/StdCppImplDataType/IDT_ADAS_enum_ObjectColor  DTE_objectColor
     */
     @SerializedName("clr")
    private IDTADASEnumObjectColor clr;
    /*
     * /DataType/StdCppImplDataType/IDT_ADAS_val_vehicleSpd  DTE_objectVelocityX
     */
     @SerializedName("vx")
    private IDTADASValVehicleSpd vx;
    /*
     * /DataType/StdCppImplDataType/IDT_ADAS_val_vehicleSpd  DTE_objectVelocityY
     */
     @SerializedName("vy")
    private IDTADASValVehicleSpd vy;
    /*
     * /DataType/StdCppImplDataType/IDT_ADAS_val_timestampnSec  DTE_timestampnSec
     */
     @SerializedName("ts")
    private IDTADASValTimestampnSec ts;
    /*
     * /DataType/StdCppImplDataType/IDT_ADAS_val_laneID  DTE_laneID
     */
     @SerializedName("lid")
    private IDTADASValLaneID lid;

    /**
     * generated from:
     * &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="f8180a3e-ee97-450c-84a2-21a13fe3d13d"&gt;
                  &lt;SHORT-NAME&gt;DTE_objectId&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_Gen_val_ID&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;

     */
    public IDTGenValID getId(){
        return this.id;
    }

    public void setId(IDTGenValID value){
        this.id=value;
    }
    /**
     * generated from:
     * &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="68bc9e88-3b74-4f61-938e-9221c251ad4a"&gt;
                  &lt;SHORT-NAME&gt;DTE_objectType&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_ADAS_enum_DynamicObjectType&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;

     */
    public IDTADASEnumDynamicObjectType getType(){
        return this.type;
    }

    public void setType(IDTADASEnumDynamicObjectType value){
        this.type=value;
    }
    /**
     * generated from:
     * &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="6be5a3df-ecb9-4a5f-ad98-8d7267229e3e"&gt;
                  &lt;SHORT-NAME&gt;DTE_lightStatus&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_ADAS_enum_LightStatus&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;

     */
    public IDTADASEnumLightStatus getLight(){
        return this.light;
    }

    public void setLight(IDTADASEnumLightStatus value){
        this.light=value;
    }
    /**
     * generated from:
     * &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="8c1870bb-7c4c-4f82-8e2e-aded02da949c"&gt;
                  &lt;SHORT-NAME&gt;DTE_objectPoseX&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_Gen_val_Coordinate_X&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;

     */
    public IDTGenValCoordinateX getX(){
        return this.x;
    }

    public void setX(IDTGenValCoordinateX value){
        this.x=value;
    }
    /**
     * generated from:
     * &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="ee3e7b5d-6bc6-425f-9cfc-e713489b72e3"&gt;
                  &lt;SHORT-NAME&gt;DTE_objectPoseY&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_Gen_val_Coordinate_Y&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;

     */
    public IDTGenValCoordinateY getY(){
        return this.y;
    }

    public void setY(IDTGenValCoordinateY value){
        this.y=value;
    }
    /**
     * generated from:
     * &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="1254e902-77da-435d-871b-bf2a52a74f80"&gt;
                  &lt;SHORT-NAME&gt;DTE_objectYaw&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_Gen_val_Yaw&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;

     */
    public IDTGenValYaw getYaw(){
        return this.yaw;
    }

    public void setYaw(IDTGenValYaw value){
        this.yaw=value;
    }
    /**
     * generated from:
     * &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="90b31beb-6480-48e4-b882-752ce3a77782"&gt;
                  &lt;SHORT-NAME&gt;DTE_objectColor&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_ADAS_enum_ObjectColor&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;

     */
    public IDTADASEnumObjectColor getClr(){
        return this.clr;
    }

    public void setClr(IDTADASEnumObjectColor value){
        this.clr=value;
    }
    /**
     * generated from:
     * &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="f3df3912-3a02-42a5-8d0d-4ab5b8cb0954"&gt;
                  &lt;SHORT-NAME&gt;DTE_objectVelocityX&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_ADAS_val_vehicleSpd&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;

     */
    public IDTADASValVehicleSpd getVx(){
        return this.vx;
    }

    public void setVx(IDTADASValVehicleSpd value){
        this.vx=value;
    }
    /**
     * generated from:
     * &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="3322d84b-e6cb-48d1-8e9c-80409943b5ce"&gt;
                  &lt;SHORT-NAME&gt;DTE_objectVelocityY&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_ADAS_val_vehicleSpd&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;

     */
    public IDTADASValVehicleSpd getVy(){
        return this.vy;
    }

    public void setVy(IDTADASValVehicleSpd value){
        this.vy=value;
    }
    /**
     * generated from:
     * &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="1f327bdd-32dc-48f8-b075-0c031e74ea6a"&gt;
                  &lt;SHORT-NAME&gt;DTE_timestampnSec&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_ADAS_val_timestampnSec&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;

     */
    public IDTADASValTimestampnSec getTs(){
        return this.ts;
    }

    public void setTs(IDTADASValTimestampnSec value){
        this.ts=value;
    }
    /**
     * generated from:
     * &lt;CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT UUID="f30e026c-59c2-4018-946e-d66ca424af7f"&gt;
                  &lt;SHORT-NAME&gt;DTE_laneID&lt;/SHORT-NAME&gt;
                  &lt;IS-OPTIONAL&gt;false&lt;/IS-OPTIONAL&gt;
                  &lt;TYPE-REFERENCE&gt;
                    &lt;TYPE-REFERENCE-REF DEST="STD-CPP-IMPLEMENTATION-DATA-TYPE"&gt;/DataType/StdCppImplDataType/IDT_ADAS_val_laneID&lt;/TYPE-REFERENCE-REF&gt;
                  &lt;/TYPE-REFERENCE&gt;
                &lt;/CPP-IMPLEMENTATION-DATA-TYPE-ELEMENT&gt;

     */
    public IDTADASValLaneID getLid(){
        return this.lid;
    }

    public void setLid(IDTADASValLaneID value){
        this.lid=value;
    }

    /**
     * read to this object from a buffer context
     */
    public void contextRead(final ByteBuffer buffer) {
            // 普通类型
            id=new IDTGenValID();
            id.contextRead(buffer);
            // 普通类型
            type=new IDTADASEnumDynamicObjectType();
            type.contextRead(buffer);
            // 普通类型
            light=new IDTADASEnumLightStatus();
            light.contextRead(buffer);
            // 普通类型
            x=new IDTGenValCoordinateX();
            x.contextRead(buffer);
            // 普通类型
            y=new IDTGenValCoordinateY();
            y.contextRead(buffer);
            // 普通类型
            yaw=new IDTGenValYaw();
            yaw.contextRead(buffer);
            // 普通类型
            clr=new IDTADASEnumObjectColor();
            clr.contextRead(buffer);
            // 普通类型
            vx=new IDTADASValVehicleSpd();
            vx.contextRead(buffer);
            // 普通类型
            vy=new IDTADASValVehicleSpd();
            vy.contextRead(buffer);
            // 普通类型
            ts=new IDTADASValTimestampnSec();
            ts.contextRead(buffer);
            // 普通类型
            lid=new IDTADASValLaneID();
            lid.contextRead(buffer);
    }
}