#include "stdafx.h"
#include "Properties/FlipperPhysicsProperty.h"
#include <WindowsX.h>

FlipperPhysicsProperty::FlipperPhysicsProperty(const VectorProtected<ISelect> *pvsel) : BasePropertyDialog(IDD_PROPFLIPPER_PHYSICS, pvsel)
{
    m_physicSetList.push_back("Disable");
    m_physicSetList.push_back("Set1");
    m_physicSetList.push_back("Set2");
    m_physicSetList.push_back("Set3");
    m_physicSetList.push_back("Set4");
    m_physicSetList.push_back("Set5");
    m_physicSetList.push_back("Set6");
    m_physicSetList.push_back("Set7");
    m_physicSetList.push_back("Set8");

    m_massEdit.SetDialog(this);
    m_strengthEdit.SetDialog(this);
    m_elasticityEdit.SetDialog(this);
    m_elasticityFalloffEdit.SetDialog(this);
    m_frictionEdit.SetDialog(this);
    m_returnStrengthEdit.SetDialog(this);
    m_coilUpRampEdit.SetDialog(this);
    m_scatterAngleEdit.SetDialog(this);
    m_eosTorqueEdit.SetDialog(this);
    m_eosTorqueAngleEdit.SetDialog(this);
    m_overwriteSettingsCombo.SetDialog(this);
}

void FlipperPhysicsProperty::UpdateVisuals(const int dispid/*=-1*/)
{
    for (int i = 0; i < m_pvsel->Size(); i++)
    {
        if ((m_pvsel->ElementAt(i) == NULL) || (m_pvsel->ElementAt(i)->GetItemType() != eItemFlipper))
            continue;
        Flipper * const flipper = (Flipper *)m_pvsel->ElementAt(i);
        if (dispid == DISPID_Flipper_Speed || dispid == -1)
            PropertyDialog::SetFloatTextbox(m_massEdit, flipper->m_d.m_mass);
        if (dispid == 19 || dispid == -1)
            PropertyDialog::SetFloatTextbox(m_strengthEdit, flipper->m_d.m_strength);
        if (dispid == 28 || dispid == -1)
            PropertyDialog::SetFloatTextbox(m_elasticityFalloffEdit, flipper->GetElastacityFalloff());
        if (dispid == 23 || dispid == -1)
            PropertyDialog::SetFloatTextbox(m_returnStrengthEdit, flipper->m_d.m_return);
        if (dispid == 27 || dispid == -1)
            PropertyDialog::SetFloatTextbox(m_coilUpRampEdit, flipper->GetRampUp());
        if (dispid == 113 || dispid == -1)
            PropertyDialog::SetFloatTextbox(m_eosTorqueEdit, flipper->m_d.m_torqueDamping);
        if (dispid == 189 || dispid == -1)
            PropertyDialog::SetFloatTextbox(m_eosTorqueAngleEdit, flipper->m_d.m_torqueDampingAngle);
        if (dispid == 1044 || dispid == -1)
            PropertyDialog::UpdateComboBox(m_physicSetList, m_overwriteSettingsCombo, m_physicSetList[flipper->m_d.m_OverridePhysics]);
        UpdateBaseVisuals(flipper, &flipper->m_d, dispid);
        //only show the first element on multi-select
        break;
    }
}

void FlipperPhysicsProperty::UpdateProperties(const int dispid)
{
    for (int i = 0; i < m_pvsel->Size(); i++)
    {
        if ((m_pvsel->ElementAt(i) == NULL) || (m_pvsel->ElementAt(i)->GetItemType() != eItemFlipper))
            continue;
        Flipper * const flipper = (Flipper *)m_pvsel->ElementAt(i);
        switch (dispid)
        {
            case 19:
                CHECK_UPDATE_ITEM(flipper->m_d.m_strength, PropertyDialog::GetFloatTextbox(m_strengthEdit), flipper);
                break;
            case 23:
                CHECK_UPDATE_VALUE_SETTER(flipper->SetReturn, flipper->GetReturn, PropertyDialog::GetFloatTextbox, m_returnStrengthEdit, flipper);
                break;
            case 27:
                CHECK_UPDATE_VALUE_SETTER(flipper->SetRampUp, flipper->GetRampUp, PropertyDialog::GetFloatTextbox, m_coilUpRampEdit, flipper);
                break;
            case 28:
                CHECK_UPDATE_VALUE_SETTER(flipper->SetElastacityFalloff, flipper->GetElastacityFalloff, PropertyDialog::GetFloatTextbox, m_elasticityFalloffEdit, flipper);
                break;
            case 113:
                CHECK_UPDATE_ITEM(flipper->m_d.m_torqueDamping, PropertyDialog::GetFloatTextbox(m_eosTorqueEdit), flipper);
                break;
            case 189:
                CHECK_UPDATE_ITEM(flipper->m_d.m_torqueDampingAngle, PropertyDialog::GetFloatTextbox(m_eosTorqueAngleEdit), flipper);
                break;
            case DISPID_Flipper_Speed:
                CHECK_UPDATE_ITEM(flipper->m_d.m_mass, PropertyDialog::GetFloatTextbox(m_massEdit), flipper);
                break;
            case 1044:
                CHECK_UPDATE_ITEM(flipper->m_d.m_OverridePhysics, (PhysicsSet)(PropertyDialog::GetComboBoxIndex(m_overwriteSettingsCombo, m_physicSetList)), flipper);
                break;
            default:
                UpdateBaseProperties(flipper, &flipper->m_d, dispid);
                break;
        }
    }
    UpdateVisuals(dispid);
}

BOOL FlipperPhysicsProperty::OnInitDialog()
{
    m_massEdit.AttachItem(DISPID_Flipper_Speed);
    m_strengthEdit.AttachItem(19);
    m_elasticityEdit.AttachItem(IDC_ELASTICITY_EDIT);
    m_baseElasticityEdit = &m_elasticityEdit;

    m_elasticityFalloffEdit.AttachItem(28);
    m_frictionEdit.AttachItem(IDC_FRICTION_EDIT);
    m_baseFrictionEdit = &m_frictionEdit;

    m_returnStrengthEdit.AttachItem(23);
    m_coilUpRampEdit.AttachItem(27);
    m_scatterAngleEdit.AttachItem(IDC_SCATTER_ANGLE_EDIT);
    m_baseScatterAngleEdit = &m_scatterAngleEdit;

    m_eosTorqueEdit.AttachItem(113);
    m_eosTorqueAngleEdit.AttachItem(189);
    m_overwriteSettingsCombo.AttachItem(1044);
    UpdateVisuals();
    return TRUE;
}

